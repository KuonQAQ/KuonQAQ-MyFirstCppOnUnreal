// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LAction.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class FCPPPROJECT_API ULAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StopAction(AActor*instigator);

	UWorld * GetWorld() const override;
};