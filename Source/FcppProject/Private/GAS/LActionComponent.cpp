// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/LActionComponent.h"

ULActionComponent::ULActionComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	
}


void ULActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for(TSubclassOf<ULAction> ActionClass: DefaultAction)
	{
		AddAction(ActionClass);
	}
	
	
}


void ULActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1,0.0f,FColor::White,DebugMsg);
}

void ULActionComponent::AddAction(TSubclassOf<ULAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}

	ULAction* NewAction= NewObject<ULAction>(this,ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool ULActionComponent::StartActionByName(AActor* instigator, FName ActionName)
{

	for(ULAction* Action:Actions)
	{
		if(Action&&Action->ActionName==ActionName)
		{
			if(!Action->CanStart(instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FailedMsg);
				continue;//继续下一个循环
			}
			Action->StartAction(instigator);
			return true;
		}
	}
	return false;
}

bool ULActionComponent::StopActionByName(AActor* instigator, FName ActionName)
{
	for(ULAction* Action:Actions)
	{
		if(Action&&Action->ActionName==ActionName)
		{
			if(Action->IsRunning())
			{
				Action->StopAction(instigator);
				return true;
			}
			
		}
	}
	return false;
}
