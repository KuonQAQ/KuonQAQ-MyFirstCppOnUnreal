// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/LAction.h"
#include "LActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API ULActionEffect : public ULAction
{
	GENERATED_BODY()
public:
	ULActionEffect();
	
	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

	
protected:
	//BUFF的持续时间。我们不希望在蓝图中修改持续时间，因此使用BlueprintReadOnly
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Duration;

	//触发BUFF的周期
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Period;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	// BUFF效果，在周期定时器触发时执行
	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
	void ExecutePeriodEffect(AActor* Instigator);
};
