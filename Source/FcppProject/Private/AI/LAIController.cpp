// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/LAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ALAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	GetBlackboardComponent()->SetValueAsObject("SelfActor",GetPawn());

	// APawn * Mypawn = UGameplayStatics::GetPlayerPawn(this,0);
	//
	// if(Mypawn)
	// {
	// 	GetBlackboardComponent()->SetValueAsVector("MovetoTarget",Mypawn->GetActorLocation());
	//
	// 	GetBlackboardComponent()->SetValueAsObject("TargetActor",Mypawn);
	// }
}
