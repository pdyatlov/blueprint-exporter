// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TestUFunctionFixtures.generated.h"

USTRUCT(BlueprintType)
struct FBpxTestFixtureStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Test)
	int32 IntField = 0;

	UPROPERTY(BlueprintReadWrite, Category = Test)
	FString StringField;

	UPROPERTY(BlueprintReadWrite, Category = Test)
	float FloatField = 0.0f;
};

UENUM(BlueprintType)
enum class EBpxTestFixtureEnum : uint8
{
	Alpha    = 0,
	Beta     = 1,
	Gamma    = 2,
};

UCLASS()
class UBpxTestUFunctionFixture : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Test)
	bool GetBoolValue() const { return true; }

	UFUNCTION(BlueprintCallable, Category = Test)
	int32 GetIntValue() const { return 42; }

	UFUNCTION(BlueprintCallable, Category = Test)
	float GetFloatValue() const { return 3.25f; }

	UFUNCTION(BlueprintCallable, Category = Test)
	FString GetStringValue() const { return TEXT("hello"); }

	UFUNCTION(BlueprintCallable, Category = Test)
	FName GetNameValue() const { return FName(TEXT("world")); }

	UFUNCTION(BlueprintCallable, Category = Test)
	UObject* GetObjectValue() { return this; }

	UFUNCTION(BlueprintCallable, Category = Test)
	int32 EchoInt(int32 Value) const { return Value; }

	UFUNCTION(BlueprintCallable, Category = Test)
	float AddFloats(float A, float B) const { return A + B; }

	UFUNCTION(BlueprintCallable, Category = Test)
	FString ConcatStrings(const FString& A, const FString& B) const { return A + B; }

	UFUNCTION(BlueprintCallable, Category = Test)
	EBpxTestFixtureEnum GetEnumValue() const { return EBpxTestFixtureEnum::Beta; }

	UFUNCTION(BlueprintCallable, Category = Test)
	FBpxTestFixtureStruct GetStructValue() const
	{
		FBpxTestFixtureStruct S;
		S.IntField = 7;
		S.StringField = TEXT("struct");
		S.FloatField = 2.5f;
		return S;
	}

	UFUNCTION(BlueprintCallable, Category = Test)
	void VoidFunction() const { /* intentional no-op for void-return test */ }
};
