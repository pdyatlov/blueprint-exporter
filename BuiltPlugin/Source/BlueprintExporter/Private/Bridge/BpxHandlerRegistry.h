// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#if WITH_BPXBRIDGE_SUPPORT

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Templates/Function.h"

namespace BlueprintExporter::Bridge
{
	struct FHandlerResult
	{
		bool bSuccess = false;
		TSharedPtr<FJsonValue> Value;
		int32 ErrorCode = 0;
		FString ErrorMessage;

		static FHandlerResult Success(TSharedPtr<FJsonValue> InValue)
		{
			FHandlerResult R;
			R.bSuccess = true;
			R.Value = MoveTemp(InValue);
			return R;
		}

		static FHandlerResult Error(int32 InCode, const FString& InMessage)
		{
			FHandlerResult R;
			R.bSuccess = false;
			R.ErrorCode = InCode;
			R.ErrorMessage = InMessage;
			return R;
		}
	};

	using FHandlerFn = TFunction<FHandlerResult(const TSharedPtr<FJsonObject>& /* Params, may be nullptr */)>;

	// Registration happens during module startup on the game thread, and the bridge server
	// reads from the same thread (libwebsockets is ticked via FTSTicker on the game thread).
	// No mutex is needed as long as registration finishes before the server starts accepting.
	class FHandlerRegistry
	{
	public:
		// Register a handler. `Description` is consumed by the M27.4 `list_methods`
		// handler so callers can discover what's available without grepping source.
		// Co-locating the description with the registration keeps them in sync —
		// adding a handler and forgetting to document it is impossible by construction
		// (you'd have to pass an empty string explicitly).
		void Register(const FString& Method, FHandlerFn Handler, const FString& Description = FString());
		bool HasHandler(const FString& Method) const;
		FHandlerFn GetHandler(const FString& Method) const;
		TArray<FString> GetMethodNames() const;
		// Returns the description passed at Register time, or empty if the method
		// isn't registered (or was registered without one).
		FString GetDescription(const FString& Method) const;

	private:
		TMap<FString, FHandlerFn> Handlers;
		TMap<FString, FString> Descriptions;
	};
}

#endif // WITH_BPXBRIDGE_SUPPORT
