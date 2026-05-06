// Copyright Ten Chambers. All Rights Reserved.

#include "BpxHandlerRegistry.h"

#if WITH_BPXBRIDGE_SUPPORT

#include "BlueprintExporterModule.h"

namespace BlueprintExporter::Bridge
{
	void FHandlerRegistry::Register(const FString& Method, FHandlerFn Handler, const FString& Description)
	{
		if (Handlers.Contains(Method))
		{
			UE_LOG(LogBlueprintExporter, Warning, TEXT("Bridge handler '%s' re-registered; overwriting previous."), *Method);
		}
		Handlers.Add(Method, MoveTemp(Handler));
		Descriptions.Add(Method, Description);
	}

	bool FHandlerRegistry::HasHandler(const FString& Method) const
	{
		return Handlers.Contains(Method);
	}

	FHandlerFn FHandlerRegistry::GetHandler(const FString& Method) const
	{
		if (const FHandlerFn* Found = Handlers.Find(Method))
		{
			return *Found;
		}
		return FHandlerFn();
	}

	TArray<FString> FHandlerRegistry::GetMethodNames() const
	{
		TArray<FString> Names;
		Handlers.GetKeys(Names);
		Names.Sort();
		return Names;
	}

	FString FHandlerRegistry::GetDescription(const FString& Method) const
	{
		if (const FString* Found = Descriptions.Find(Method))
		{
			return *Found;
		}
		return FString();
	}
}

#endif // WITH_BPXBRIDGE_SUPPORT
