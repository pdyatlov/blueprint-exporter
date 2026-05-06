// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

/**
 * Resolution state for a pin type - single source of truth
 */
enum class EResolutionState : uint8
{
	UnrealResolved,  // Engine provided this type
	Inferred,        // We inferred this type from connections
	Conflict,        // Multiple conflicting types from connections
	Unresolved       // Unknown type, no inference possible
};

/**
 * High-level type kind classification
 */
enum class ETypeKind : uint8
{
	Object,
	Struct,
	Class,
	Enum,
	Interface,
	Primitive,
	Exec,
	Wildcard,
	Context,
	Unknown
};

/**
 * Container type for pins
 */
enum class EContainerType : uint8
{
	None,
	Array,
	Set,
	Map
};

/**
 * Type signature for comparison and unification
 */
struct FTypeSignature
{
	ETypeKind Kind = ETypeKind::Unknown;
	FString Category;      // UE pin category: "real", "int", "bool", "object", "struct", etc.
	FString Path;          // Normalized path: "/Script/CoreUObject.Vector"
	EContainerType Container = EContainerType::None;

	// Container element types
	TOptional<TSharedPtr<FTypeSignature>> ElementType;    // For array/set
	TOptional<TSharedPtr<FTypeSignature>> MapKeyType;     // For map
	TOptional<TSharedPtr<FTypeSignature>> MapValueType;   // For map

	bool bIsReference = false;
	bool bIsConst = false;

	/** Check if this is a concrete type (can be used for inference) */
	bool IsConcrete(int32 Depth = 0) const;

	/** Check if types are equal for unification */
	bool Equals(const FTypeSignature& Other) const;

	/** Get hash for deduplication */
	FString GetHash() const;

	/** Check if this kind needs a path to be valid */
	static bool NeedsPath(ETypeKind InKind);

	/** Convert kind to string */
	static FString KindToString(ETypeKind InKind);

	/** Convert container to string */
	static FString ContainerToString(EContainerType InContainer);

	/** Parse kind from string */
	static ETypeKind ParseKind(const FString& Str);

	/** Parse container from string */
	static EContainerType ParseContainer(const FString& Str);
};

/**
 * Reference to a pin for provenance tracking
 */
struct FPinReference
{
	FString GraphScope;
	FString NodeGuid;
	FString PinName;
	FString Direction;

	FString MakeId() const;
};

/**
 * Internal pin data during inference
 */
struct FInferencePinData
{
	TSharedPtr<FJsonObject> TypeObject;
	TSharedPtr<FJsonObject> PinObject;
	TSharedPtr<FJsonObject> NodeObject;
	FString GraphScope;

	// Stable IDs (used for connections) - PRIMARY keys
	FString NodeId;      // e.g., "Call_GetData_123_456"
	FString PinId;       // e.g., "Out_ReturnValue" (includes direction)

	// Internal names (for reference)
	FString NodeGuid;    // UE internal GUID
	FString PinName;     // e.g., "ReturnValue"
	FString Direction;   // "Input" or "Output"

	FString NodeClass;

	EResolutionState State = EResolutionState::Unresolved;
	int32 InferredPass = 0;
	FString UnresolvedReason;
	bool bInvariantViolation = false;
	bool bIsReroute = false;
	bool bPossibleInterface = false;

	FTypeSignature ExtractedSignature;
	TArray<FPinReference> InferredFrom;
	TArray<FTypeSignature> ConflictingTypes;

	bool IsResolved() const { return State == EResolutionState::UnrealResolved || State == EResolutionState::Inferred; }
	bool HasConflict() const { return State == EResolutionState::Conflict; }
};

/**
 * Inference statistics for the export
 */
struct FInferenceStats
{
	// Total counts
	int32 TotalPins = 0;
	int32 ResolvedPins = 0;      // UnrealResolved + Inferred
	int32 UnresolvedPins = 0;
	int32 ConflictPins = 0;

	// Breakdown of resolved
	int32 UnrealResolvedPins = 0;
	int32 InferredPins = 0;

	// Complex-only view (excludes primitives/exec)
	int32 TotalComplexPins = 0;
	int32 UnrealResolvedComplexPins = 0;
	int32 InferredComplexPins = 0;
	int32 UnresolvedComplexPins = 0;

	int32 PassesRun = 0;

	TSharedPtr<FJsonObject> ToJson() const;
};

/**
 * Type inference engine for Blueprint exports.
 * Runs as a post-processing pass on JSON to infer missing types from connections.
 */
class BLUEPRINTEXPORTER_API FBlueprintTypeInference
{
public:
	FBlueprintTypeInference();
	~FBlueprintTypeInference();

	/**
	 * Run type inference on an exported Blueprint JSON.
	 * @param ExportJson The JSON object from serialization
	 * @param MaxPasses Maximum inference passes (default 10)
	 * @return Inference statistics
	 */
	FInferenceStats RunTypeInference(TSharedPtr<FJsonObject> ExportJson, int32 MaxPasses = 10);

private:
	/** Build pin lookup map from JSON */
	void BuildPinLookup(TSharedPtr<FJsonObject> ExportJson);

	/** Build bidirectional connection graph */
	void BuildConnectionGraph(TSharedPtr<FJsonObject> ExportJson);

	/** Extract type signature from JSON type object */
	FTypeSignature ExtractTypeSignature(TSharedPtr<FJsonObject> TypeObj);

	/** Apply inferred type to JSON */
	void ApplyInferredType(FInferencePinData& Pin, const FTypeSignature& Type, int32 Pass, const TArray<FPinReference>& Sources);

	/** Mark pin as having conflicting types */
	void MarkTypeConflict(FInferencePinData& Pin, const TArray<FTypeSignature>& ConflictingTypes);

	/** Set pin state with proper metadata cleanup */
	void SetPinState(FInferencePinData& Pin, EResolutionState NewState, int32 InferPass = 0, const FString& Reason = TEXT(""));

	/** Run hard inference pass (direct wire connections) */
	int32 RunHardInferencePass(int32 Pass);

	/** Run soft inference pass (type carrier nodes) */
	int32 RunSoftInferencePass(int32 Pass);

	/** Try to unify multiple types into one */
	TOptional<FTypeSignature> TryUnify(const TArray<FTypeSignature>& Types);

	/** Mark static function self pins specially */
	void MarkStaticFunctionSelfPins(TSharedPtr<FJsonObject> ExportJson);

	/** Finalize all pin metadata in JSON */
	void FinalizeAllPinMetadata();

	/** Compute inference stats */
	FInferenceStats ComputeStats();

	/** Write inference stats to JSON */
	void WriteInferenceStats(TSharedPtr<FJsonObject> ExportJson, const FInferenceStats& Stats);

public:
	/** Normalize a type path - public for use by FTypeSignature */
	static FString NormalizePath(const FString& Path);

private:

	/** Determine type kind from category and path */
	static ETypeKind DetermineKind(const FString& Category, const FString& SubCategoryPath, bool& bOutPossibleInterface);

	/** Check if a type is complex (needs inference) */
	static bool IsComplexType(const FInferencePinData& Pin);

	/** Process a graph and its nodes for pin lookup */
	void ProcessGraph(TSharedPtr<FJsonObject> GraphObj, const FString& GraphScope);

	/** Process connections for a single node */
	void ProcessNodeConnections(TSharedPtr<FJsonObject> NodeObj, const FString& GraphScope);

	/** Known type carrier node classes */
	static const TSet<FString>& GetTypeCarrierNodes();

private:
	/** Pin lookup: "GraphScope:NodeGuid:PinName:Direction" -> pin data */
	TMap<FString, FInferencePinData> PinLookup;

	/** Connection graph: pin id -> connected pin ids */
	TMultiMap<FString, FString> Connections;

	/** Set of resolved pin IDs */
	TSet<FString> ResolvedPins;

	/** Set of potential conflict pin IDs (deferred until after convergence) */
	TSet<FString> PotentialConflicts;

	/** Blueprint class path for context pins */
	FString BlueprintClassPath;
};
