// Copyright 10 Chambers. All Rights Reserved.

#include "Util/AtomicFileWriter.h"

#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

namespace BlueprintExporterUtil
{
	bool SaveStringAtomic(const FString& Content, const FString& FinalPath)
	{
		const FString TmpPath = FinalPath + TEXT(".tmp");
		if (!FFileHelper::SaveStringToFile(Content, *TmpPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			return false;
		}
		IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
		if (PF.FileExists(*FinalPath))
		{
			PF.DeleteFile(*FinalPath);
		}
		return PF.MoveFile(*FinalPath, *TmpPath);
	}
}
