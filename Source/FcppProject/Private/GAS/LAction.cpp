// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/LAction.h"

void ULAction::StartAction_Implementation(AActor* Instigator)
{
	ULActionComponent * comp=GetOwingComponent();
	comp->ActiveGameplayTags.AppendTags(GrantsTags);
	UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(this));

	bIsRunning=true;
}

void ULAction::StopAction_Implementation(AActor* instigator)
{

	ensureAlways(bIsRunning);
	
	ULActionComponent * comp=GetOwingComponent();
	comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	UE_LOG(LogTemp,Log,TEXT("Stop:%s"),*GetNameSafe(this));

	bIsRunning=false;
}

bool ULAction::CanStart_Implementation(AActor* intigator)
{
	if(IsRunning())
	{
		return false;
	}
	
	ULActionComponent * comp=GetOwingComponent();
	if(comp->ActiveGameplayTags.HasAny(BlockTags))
	{
		return false;
	}
	return true;
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

bool ULAction::IsRunning() const
{
	return bIsRunning;
}

ULActionComponent* ULAction::GetOwingComponent() const
{
	return Cast<ULActionComponent>(GetOuter());
}
