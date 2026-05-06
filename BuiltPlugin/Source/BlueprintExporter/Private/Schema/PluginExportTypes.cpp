// Copyright 10 Chambers. All Rights Reserved.

#include "Schema/PluginExportTypes.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Misc/SecureHash.h"

// --------------------------------- FExportedReflectedProperty ---------------------------------

TSharedPtr<FJsonObject> FExportedReflectedProperty::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
	Json->SetStringField(TEXT("name"), Name);
	Json->SetStringField(TEXT("type"), Type);
	Json->SetStringField(TEXT("value"), Value);
	if (!Category.IsEmpty())
	{
		Json->SetStringField(TEXT("category"), Category);
	}
	return Json;
}

FExportedReflectedProperty FExportedReflectedProperty::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FExportedReflectedProperty Property;
	if (Json.IsValid())
	{
		Json->TryGetStringField(TEXT("name"), Property.Name);
		Json->TryGetStringField(TEXT("type"), Property.Type);
		Json->TryGetStringField(TEXT("value"), Property.Value);
		Json->TryGetStringField(TEXT("category"), Property.Category);
	}
	return Property;
}

// --------------------------------- FExportedPluginModule ---------------------------------

TSharedPtr<FJsonObject> FExportedPluginModule::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
	Json->SetStringField(TEXT("name"), Name);
	Json->SetStringField(TEXT("hostType"), HostType);
	Json->SetStringField(TEXT("loadingPhase"), LoadingPhase);
	return Json;
}

FExportedPluginModule FExportedPluginModule::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FExportedPluginModule Module;
	if (Json.IsValid())
	{
		Json->TryGetStringField(TEXT("name"), Module.Name);
		Json->TryGetStringField(TEXT("hostType"), Module.HostType);
		Json->TryGetStringField(TEXT("loadingPhase"), Module.LoadingPhase);
	}
	return Module;
}

// --------------------------------- FExportedPluginDependency ---------------------------------

TSharedPtr<FJsonObject> FExportedPluginDependency::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
	Json->SetStringField(TEXT("name"), Name);
	Json->SetBoolField(TEXT("enabled"), bEnabled);
	Json->SetBoolField(TEXT("optional"), bOptional);
	return Json;
}

FExportedPluginDependency FExportedPluginDependency::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FExportedPluginDependency Dep;
	if (Json.IsValid())
	{
		Json->TryGetStringField(TEXT("name"), Dep.Name);
		Json->TryGetBoolField(TEXT("enabled"), Dep.bEnabled);
		Json->TryGetBoolField(TEXT("optional"), Dep.bOptional);
	}
	return Dep;
}

// --------------------------------- FExportedPluginNativeType ---------------------------------

TSharedPtr<FJsonObject> FExportedPluginNativeType::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
	Json->SetStringField(TEXT("classPath"), ClassPath);
	Json->SetStringField(TEXT("parentClassPath"), ParentClassPath);
	Json->SetStringField(TEXT("moduleName"), ModuleName);
	if (!Subsystem.IsEmpty())
	{
		Json->SetStringField(TEXT("subsystem"), Subsystem);
	}

	// Properties — sorted alpha by name for determinism (brief §8).
	TArray<FExportedReflectedProperty> Sorted = Properties;
	Sorted.Sort([](const FExportedReflectedProperty& A, const FExportedReflectedProperty& B)
	{
		return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
	});

	TArray<TSharedPtr<FJsonValue>> PropsArray;
	for (const FExportedReflectedProperty& Prop : Sorted)
	{
		PropsArray.Add(MakeShareable(new FJsonValueObject(Prop.ToJson())));
	}
	if (PropsArray.Num() > 0)
	{
		Json->SetArrayField(TEXT("properties"), PropsArray);
	}

	return Json;
}

FExportedPluginNativeType FExportedPluginNativeType::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FExportedPluginNativeType Type;
	if (Json.IsValid())
	{
		Json->TryGetStringField(TEXT("classPath"), Type.ClassPath);
		Json->TryGetStringField(TEXT("parentClassPath"), Type.ParentClassPath);
		Json->TryGetStringField(TEXT("moduleName"), Type.ModuleName);
		Json->TryGetStringField(TEXT("subsystem"), Type.Subsystem);

		const TArray<TSharedPtr<FJsonValue>>* PropsArray = nullptr;
		if (Json->TryGetArrayField(TEXT("properties"), PropsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *PropsArray)
			{
				Type.Properties.Add(FExportedReflectedProperty::FromJson(Value->AsObject()));
			}
		}
	}
	return Type;
}

// --------------------------------- FExportedPlugin ---------------------------------

TSharedPtr<FJsonObject> FExportedPlugin::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
	Json->SetObjectField(TEXT("exportInfo"), ExportInfo.ToJson());
	Json->SetStringField(TEXT("name"), Name);
	Json->SetStringField(TEXT("pluginType"), PluginType);
	Json->SetStringField(TEXT("baseDir"), BaseDir);
	Json->SetBoolField(TEXT("enabled"), bEnabled);
	Json->SetNumberField(TEXT("version"), Version);
	Json->SetStringField(TEXT("versionName"), VersionName);
	if (!FriendlyName.IsEmpty())    Json->SetStringField(TEXT("friendlyName"), FriendlyName);
	if (!Description.IsEmpty())     Json->SetStringField(TEXT("description"), Description);
	if (!Category.IsEmpty())        Json->SetStringField(TEXT("category"), Category);
	if (!CreatedBy.IsEmpty())       Json->SetStringField(TEXT("createdBy"), CreatedBy);
	if (!CreatedByURL.IsEmpty())    Json->SetStringField(TEXT("createdByURL"), CreatedByURL);
	if (!DocsURL.IsEmpty())         Json->SetStringField(TEXT("docsURL"), DocsURL);
	if (!SupportURL.IsEmpty())      Json->SetStringField(TEXT("supportURL"), SupportURL);
	if (!EngineVersion.IsEmpty())   Json->SetStringField(TEXT("engineVersion"), EngineVersion);
	Json->SetBoolField(TEXT("canContainContent"), bCanContainContent);
	if (bIsBetaVersion)             Json->SetBoolField(TEXT("isBetaVersion"), bIsBetaVersion);
	if (bInstalled)                 Json->SetBoolField(TEXT("installed"), bInstalled);

	// Modules — sorted alpha by name.
	TArray<FExportedPluginModule> SortedModules = Modules;
	SortedModules.Sort([](const FExportedPluginModule& A, const FExportedPluginModule& B)
	{
		return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
	});
	TArray<TSharedPtr<FJsonValue>> ModulesArray;
	for (const FExportedPluginModule& M : SortedModules)
	{
		ModulesArray.Add(MakeShareable(new FJsonValueObject(M.ToJson())));
	}
	Json->SetArrayField(TEXT("modules"), ModulesArray);

	// Plugin dependencies — sorted alpha by name.
	TArray<FExportedPluginDependency> SortedDeps = PluginDependencies;
	SortedDeps.Sort([](const FExportedPluginDependency& A, const FExportedPluginDependency& B)
	{
		return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
	});
	TArray<TSharedPtr<FJsonValue>> DepsArray;
	for (const FExportedPluginDependency& D : SortedDeps)
	{
		DepsArray.Add(MakeShareable(new FJsonValueObject(D.ToJson())));
	}
	Json->SetArrayField(TEXT("pluginDependencies"), DepsArray);

	// Native types — only written when non-empty (P1 populates; P0 omits the field).
	if (NativeTypes.Num() > 0)
	{
		TArray<FExportedPluginNativeType> SortedTypes = NativeTypes;
		SortedTypes.Sort([](const FExportedPluginNativeType& A, const FExportedPluginNativeType& B)
		{
			return A.ClassPath.Compare(B.ClassPath, ESearchCase::IgnoreCase) < 0;
		});
		TArray<TSharedPtr<FJsonValue>> TypesArray;
		for (const FExportedPluginNativeType& T : SortedTypes)
		{
			TypesArray.Add(MakeShareable(new FJsonValueObject(T.ToJson())));
		}
		Json->SetArrayField(TEXT("nativeTypes"), TypesArray);
	}

	return Json;
}

FExportedPlugin FExportedPlugin::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FExportedPlugin Plugin;
	if (!Json.IsValid())
	{
		return Plugin;
	}

	const TSharedPtr<FJsonObject>* ExportInfoJson = nullptr;
	if (Json->TryGetObjectField(TEXT("exportInfo"), ExportInfoJson) && ExportInfoJson && ExportInfoJson->IsValid())
	{
		Plugin.ExportInfo = FExportInfo::FromJson(*ExportInfoJson);
	}

	Json->TryGetStringField(TEXT("name"), Plugin.Name);
	Json->TryGetStringField(TEXT("pluginType"), Plugin.PluginType);
	Json->TryGetStringField(TEXT("baseDir"), Plugin.BaseDir);
	Json->TryGetBoolField(TEXT("enabled"), Plugin.bEnabled);
	{
		int32 VersionInt = 0;
		if (Json->TryGetNumberField(TEXT("version"), VersionInt))
		{
			Plugin.Version = VersionInt;
		}
	}
	Json->TryGetStringField(TEXT("versionName"), Plugin.VersionName);
	Json->TryGetStringField(TEXT("friendlyName"), Plugin.FriendlyName);
	Json->TryGetStringField(TEXT("description"), Plugin.Description);
	Json->TryGetStringField(TEXT("category"), Plugin.Category);
	Json->TryGetStringField(TEXT("createdBy"), Plugin.CreatedBy);
	Json->TryGetStringField(TEXT("createdByURL"), Plugin.CreatedByURL);
	Json->TryGetStringField(TEXT("docsURL"), Plugin.DocsURL);
	Json->TryGetStringField(TEXT("supportURL"), Plugin.SupportURL);
	Json->TryGetStringField(TEXT("engineVersion"), Plugin.EngineVersion);
	Json->TryGetBoolField(TEXT("canContainContent"), Plugin.bCanContainContent);
	Json->TryGetBoolField(TEXT("isBetaVersion"), Plugin.bIsBetaVersion);
	Json->TryGetBoolField(TEXT("installed"), Plugin.bInstalled);

	const TArray<TSharedPtr<FJsonValue>>* ModulesArray = nullptr;
	if (Json->TryGetArrayField(TEXT("modules"), ModulesArray))
	{
		for (const TSharedPtr<FJsonValue>& V : *ModulesArray)
		{
			Plugin.Modules.Add(FExportedPluginModule::FromJson(V->AsObject()));
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* DepsArray = nullptr;
	if (Json->TryGetArrayField(TEXT("pluginDependencies"), DepsArray))
	{
		for (const TSharedPtr<FJsonValue>& V : *DepsArray)
		{
			Plugin.PluginDependencies.Add(FExportedPluginDependency::FromJson(V->AsObject()));
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* TypesArray = nullptr;
	if (Json->TryGetArrayField(TEXT("nativeTypes"), TypesArray))
	{
		for (const TSharedPtr<FJsonValue>& V : *TypesArray)
		{
			Plugin.NativeTypes.Add(FExportedPluginNativeType::FromJson(V->AsObject()));
		}
	}

	return Plugin;
}

FString FExportedPlugin::ComputeContentHash() const
{
	FExportedPlugin HashCopy = *this;
	HashCopy.ExportInfo.ExportTimestamp = TEXT("");
	HashCopy.ExportInfo.ContentHash = TEXT("");

	const TSharedPtr<FJsonObject> Json = HashCopy.ToJson();
	FString JsonString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
	return FMD5::HashAnsiString(*JsonString);
}
