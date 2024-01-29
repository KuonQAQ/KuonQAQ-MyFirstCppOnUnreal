// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/LAction.h"

void ULAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(this));
}

void ULAction::StopAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stop:%s"),*GetNameSafe(this));
}

UWorld* ULAction::GetWorld() const
{
	// 因为Action是由组件生成的，这里就转化为组件
	//Outer在UObject创建时传入
	UActorComponent* ActorComponent = Cast<UActorComponent>( GetOuter());
	if(ActorComponent)
	{
		return ActorComponent->GetWorld();
	}
	return nullptr;
}
