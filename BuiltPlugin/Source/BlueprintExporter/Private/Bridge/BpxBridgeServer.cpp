// Copyright Ten Chambers. All Rights Reserved.

#include "BpxBridgeServer.h"

#if WITH_BPXBRIDGE_SUPPORT

#include "BlueprintExporterModule.h"
#include "BpxJsonRpcErrors.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "INetworkingWebSocket.h"
#include "IWebSocketNetworkingModule.h"
#include "IWebSocketServer.h"
#include "Modules/ModuleManager.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "WebSocketNetworkingDelegates.h"

namespace BlueprintExporter::Bridge
{
	namespace
	{
		TSharedPtr<FJsonValue> MakeNullId()
		{
			return MakeShared<FJsonValueNull>();
		}

		FString SerializeResponse(TSharedPtr<FJsonValue> Id, TSharedPtr<FJsonObject> ResponseObj)
		{
			ResponseObj->SetStringField(TEXT("jsonrpc"), TEXT("2.0"));
			ResponseObj->SetField(TEXT("id"), Id.IsValid() ? Id : MakeNullId());

			FString Out;
			TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer =
				TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
			FJsonSerializer::Serialize(ResponseObj.ToSharedRef(), Writer);
			return Out;
		}
	}

	FBridgeServer::FBridgeServer() = default;

	FBridgeServer::~FBridgeServer()
	{
		Stop();
	}

	bool FBridgeServer::Start(uint16 Port, FHandlerRegistry* InRegistry)
	{
		if (Server.IsValid())
		{
			UE_LOG(LogBlueprintExporter, Warning, TEXT("Bridge server already running on port %u; Start() ignored."), CurrentPort);
			return true;
		}

		Registry = InRegistry;
		CurrentPort = Port;

		IWebSocketNetworkingModule* WsModule = FModuleManager::Get().LoadModulePtr<IWebSocketNetworkingModule>(TEXT("WebSocketNetworking"));
		if (!WsModule)
		{
			UE_LOG(LogBlueprintExporter, Warning, TEXT("Bridge server: WebSocketNetworking module not available; bridge disabled."));
			return false;
		}

		Server = WsModule->CreateServer();
		if (!Server.IsValid())
		{
			UE_LOG(LogBlueprintExporter, Error, TEXT("Bridge server: CreateServer() returned null."));
			return false;
		}

		FWebSocketClientConnectedCallBack ConnectedCallback;
		ConnectedCallback.BindThreadSafeSP(AsShared(), &FBridgeServer::OnClientConnected);

		// Bind to loopback only — bridge is an internal dev tool, never exposed to the network.
		const FString BindAddress = TEXT("127.0.0.1");
		if (!Server->Init(Port, ConnectedCallback, BindAddress))
		{
			UE_LOG(LogBlueprintExporter, Error, TEXT("Bridge server: failed to bind on %s:%u (port in use?)."), *BindAddress, Port);
			Server.Reset();
			return false;
		}

		TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateThreadSafeSP(AsShared(), &FBridgeServer::ServerTick));

		UE_LOG(LogBlueprintExporter, Log, TEXT("Bridge server listening on 127.0.0.1:%u"), Port);
		return true;
	}

	void FBridgeServer::Stop()
	{
		if (TickerHandle.IsValid())
		{
			FTSTicker::RemoveTicker(TickerHandle);
			TickerHandle.Reset();
		}
		if (Server.IsValid())
		{
			Server.Reset();
			UE_LOG(LogBlueprintExporter, Log, TEXT("Bridge server stopped."));
		}
		Registry = nullptr;
		CurrentPort = 0;
	}

	bool FBridgeServer::ServerTick(float /*DeltaTime*/)
	{
		if (Server.IsValid())
		{
			Server->Tick();
		}
		return true;
	}

	void FBridgeServer::OnClientConnected(INetworkingWebSocket* Socket)
	{
		if (!Socket)
		{
			return;
		}

		UE_LOG(LogBlueprintExporter, Verbose, TEXT("Bridge: client connected from %s"), *Socket->RemoteEndPoint(true));

		TWeakPtr<FBridgeServer, ESPMode::ThreadSafe> WeakSelf = AsShared();
		Socket->SetReceiveCallBack(FWebSocketPacketReceivedCallBack::CreateLambda(
			[WeakSelf, Socket](void* Data, int32 Size)
			{
				if (TSharedPtr<FBridgeServer, ESPMode::ThreadSafe> Self = WeakSelf.Pin())
				{
					Self->OnMessageReceived(Socket, Data, Size);
				}
			}));
	}

	void FBridgeServer::OnMessageReceived(INetworkingWebSocket* Socket, void* Data, int32 Size)
	{
		if (!Socket || Size <= 0 || !Data)
		{
			return;
		}

		// Data is UTF-8 bytes of a JSON-RPC 2.0 request; decode to FString.
		FString Payload;
		{
			FUTF8ToTCHAR Conv(reinterpret_cast<const ANSICHAR*>(Data), Size);
			Payload.AppendChars(Conv.Get(), Conv.Length());
		}

		TSharedPtr<FJsonObject> RequestObj;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Payload);
		if (!FJsonSerializer::Deserialize(Reader, RequestObj) || !RequestObj.IsValid())
		{
			SendError(Socket, MakeNullId(), ErrParse, TEXT("Parse error: payload is not valid JSON."));
			return;
		}

		DispatchRequest(Socket, RequestObj);
	}

	void FBridgeServer::DispatchRequest(INetworkingWebSocket* Socket, const TSharedPtr<FJsonObject>& Request)
	{
		TSharedPtr<FJsonValue> Id = Request->TryGetField(TEXT("id"));

		FString Method;
		if (!Request->TryGetStringField(TEXT("method"), Method) || Method.IsEmpty())
		{
			SendError(Socket, Id, ErrInvalidRequest, TEXT("Invalid Request: 'method' is required and must be a non-empty string."));
			return;
		}

		FString JsonRpcVersion;
		if (!Request->TryGetStringField(TEXT("jsonrpc"), JsonRpcVersion) || JsonRpcVersion != TEXT("2.0"))
		{
			SendError(Socket, Id, ErrInvalidRequest, TEXT("Invalid Request: 'jsonrpc' must be '2.0'."));
			return;
		}

		if (!Registry || !Registry->HasHandler(Method))
		{
			SendError(Socket, Id, ErrMethodNotFound, FString::Printf(TEXT("Method not found: '%s'."), *Method));
			return;
		}

		TSharedPtr<FJsonObject> Params;
		const TSharedPtr<FJsonObject>* ParamsObj = nullptr;
		if (Request->TryGetObjectField(TEXT("params"), ParamsObj) && ParamsObj)
		{
			Params = *ParamsObj;
		}

		FHandlerFn Handler = Registry->GetHandler(Method);
		FHandlerResult Result;
		try
		{
			Result = Handler(Params);
		}
		catch (...)
		{
			SendError(Socket, Id, ErrInternal, FString::Printf(TEXT("Internal error: handler '%s' threw."), *Method));
			return;
		}

		if (!Result.bSuccess)
		{
			SendError(Socket, Id, Result.ErrorCode != 0 ? Result.ErrorCode : ErrInternal, Result.ErrorMessage);
			return;
		}

		TSharedPtr<FJsonObject> ResponseObj = MakeShared<FJsonObject>();
		ResponseObj->SetField(TEXT("result"), Result.Value.IsValid() ? Result.Value : MakeNullId());
		SendResponse(Socket, SerializeResponse(Id, ResponseObj));
	}

	void FBridgeServer::SendResponse(INetworkingWebSocket* Socket, const FString& Json)
	{
		if (!Socket)
		{
			return;
		}
		FTCHARToUTF8 Utf8(*Json);
		Socket->Send(reinterpret_cast<const uint8*>(Utf8.Get()), Utf8.Length(), /*bPrependSize*/ false);
	}

	void FBridgeServer::SendError(INetworkingWebSocket* Socket, TSharedPtr<FJsonValue> Id, int32 Code, const FString& Message)
	{
		TSharedPtr<FJsonObject> ErrorObj = MakeShared<FJsonObject>();
		ErrorObj->SetNumberField(TEXT("code"), Code);
		ErrorObj->SetStringField(TEXT("message"), Message);

		TSharedPtr<FJsonObject> ResponseObj = MakeShared<FJsonObject>();
		ResponseObj->SetObjectField(TEXT("error"), ErrorObj);

		SendResponse(Socket, SerializeResponse(Id, ResponseObj));
	}
}

#endif // WITH_BPXBRIDGE_SUPPORT
