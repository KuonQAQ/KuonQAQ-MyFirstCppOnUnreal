// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_AttackRange.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API UTask_AttackRange : public UBTTaskNode
{
	GENERATED_BODY()

	UTask_AttackRange();
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	float AttackCD;

	UPROPERTY(EditAnywhere)
	float MaxBulletSpread;
	
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
