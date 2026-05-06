// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ReflectionTypes.generated.h"

/**
 * Result of a reflection-bridge op. Returned by UBpxReflectionOps methods
 * so Python callers get uniform before / after / error data without needing
 * to parse log output.
 */
USTRUCT(BlueprintType)
struct BLUEPRINTEXPORTER_API FBpxReflectionResult
{
	GENERATED_BODY()

	/** True iff the op completed successfully. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	bool bSuccess = false;

	/** Human-readable error message. Empty on success. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FString ErrorMessage;

	/** ExportText of the property value before the op. Empty for pure-read ops. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FString BeforeText;

	/** ExportText of the property value after the op. Populated on success. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FString AfterText;

	/** True when the op was a no-op because BeforeText already matched the target. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	bool bSkipped = false;
};

/**
 * Entry / Return node GUIDs for a Blueprint function graph. M26.1 — callers
 * use these to reference Entry and Return by stable GUID in subsequent ops
 * (AddSelfMemberGetNode targets the graph by function name; pins are wired
 * by referencing these GUIDs).
 *
 * GUIDs are deterministic: OverrideInterfaceFunction seeds Entry / Return
 * NodeGuids from md5(bp_path + ":" + function_name + ":entry|return"),
 * overriding UE's internal `FGuid::NewGuid()` so the golden post-op BugHunt
 * fixture stays byte-identical across re-generation.
 */
USTRUCT(BlueprintType)
struct BLUEPRINTEXPORTER_API FBpxGraphEndpoints
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	bool bSuccess = false;

	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FString ErrorMessage;

	/** GUID of the UK2Node_FunctionEntry node in the target function graph. Zero on error. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FGuid EntryGuid;

	/** GUID of the UK2Node_FunctionResult node in the target function graph.
	 *  Zero if the function has no return (void / latent FUNC_Event signatures). */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FGuid ReturnGuid;

	/** True when the op was a no-op because an equivalent function graph
	 *  already existed (M28.2.2 AddFunctionGraphDeterministic idempotent skip). */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	bool bSkipped = false;
};

/**
 * Result of a node-creation op. M26.1 — AddSelfMemberGetNode (and future node-
 * creation ops) return the newly-created node's GUID so callers can chain
 * subsequent ConnectPinsByName / SetNodePinLiteralDefault calls by GUID
 * rather than by walking the graph.
 */
USTRUCT(BlueprintType)
struct BLUEPRINTEXPORTER_API FBpxNodeResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	bool bSuccess = false;

	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FString ErrorMessage;

	/** Deterministic GUID of the newly-created (or re-found, on idempotent skip) node. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	FGuid NodeGuid;

	/** True when the op was a no-op because an equivalent node already existed. */
	UPROPERTY(BlueprintReadOnly, Category = "Reflection")
	bool bSkipped = false;
};
