// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LActionComponent.h"
#include "LAction.generated.h"


UCLASS(Blueprintable)
class FCPPPROJECT_API ULAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent)
	bool CanStart(AActor*intigator);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action")
	void StopAction(AActor*instigator);

	UWorld * GetWorld() const override;

	UFUNCTION(BlueprintCallable,Category="Action")
	bool IsRunning() const;

protected:
    //action本身的属性
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer GrantsTags;
    /* 和哪些tag互斥 */
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer BlockTags;

	bool bIsRunning;

	UFUNCTION(BlueprintCallable,Category="Action")
	ULActionComponent* GetOwingComponent() const;
};
