// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LAIController.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API ALAIController : public AAIController
{
	GENERATED_BODY()
protected:
UPROPERTY(EditAnywhere)
	UBehaviorTree * BehaviorTree;

	virtual void BeginPlay() override;
	
};
