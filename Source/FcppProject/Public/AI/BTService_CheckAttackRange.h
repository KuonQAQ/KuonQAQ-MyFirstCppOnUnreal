// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API UBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector  CheackAttackRange;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
