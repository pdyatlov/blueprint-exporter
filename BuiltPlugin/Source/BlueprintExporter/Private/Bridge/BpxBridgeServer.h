// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#if WITH_BPXBRIDGE_SUPPORT

#include "CoreMinimal.h"
#include "BpxHandlerRegistry.h"
#include "Containers/Ticker.h"
#include "Templates/SharedPointer.h"
#include "Templates/UniquePtr.h"

class IWebSocketServer;
class INetworkingWebSocket;

namespace BlueprintExporter::Bridge
{
	// JSON-RPC 2.0 server bound to a local loopback port. One instance is owned by the module.
	// Tick runs on the game thread via FTSTicker::GetCoreTicker(); libwebsockets delivers
	// client-connect + receive callbacks during that tick, so all handler dispatch happens
	// on the game thread with no cross-thread marshaling.
	class FBridgeServer : public TSharedFromThis<FBridgeServer, ESPMode::ThreadSafe>
	{
	public:
		// Constructor + destructor defined out-of-line so TUniquePtr<IWebSocketServer>
		// can use a forward declaration here (deleter needs the complete type).
		FBridgeServer();
		~FBridgeServer();

		// Returns false if the WebSocketNetworking module is missing or the port is in use.
		bool Start(uint16 Port, FHandlerRegistry* InRegistry);

		void Stop();

		bool IsRunning() const { return Server.IsValid(); }
		uint16 GetPort() const { return CurrentPort; }

	private:
		bool ServerTick(float DeltaTime);
		void OnClientConnected(INetworkingWebSocket* Socket);
		void OnMessageReceived(INetworkingWebSocket* Socket, void* Data, int32 Size);
		void DispatchRequest(INetworkingWebSocket* Socket, const TSharedPtr<FJsonObject>& Request);
		void SendResponse(INetworkingWebSocket* Socket, const FString& Json);
		void SendError(INetworkingWebSocket* Socket, TSharedPtr<FJsonValue> Id, int32 Code, const FString& Message);

		TUniquePtr<IWebSocketServer> Server;
		FHandlerRegistry* Registry = nullptr;
		FTSTicker::FDelegateHandle TickerHandle;
		uint16 CurrentPort = 0;
	};
}

#endif // WITH_BPXBRIDGE_SUPPORT
