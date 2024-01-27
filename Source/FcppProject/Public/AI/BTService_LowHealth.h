// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_LowHealth.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API UBTService_LowHealth : public UBTService
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LowHealth;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
