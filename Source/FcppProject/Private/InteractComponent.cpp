// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "DrawDebugHelpers.h"
#include "GameplayInterface.h"
#include "LCharacter.h"
#include "Camera/CameraComponent.h"


static  TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDeaw"), false, TEXT("Enable Debug Line for Interact Component."), ECVF_Cheat);
// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	LineLength = 700.0f;

	// ...
}




// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	FVector End;
	//FHitResult Hit;
	TArray<FHitResult> Hits;

	float Radius = 30.0f;
	
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	FVector Eyelocation;
	FRotator EyeRotator;
	
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor * owner = GetOwner();
	owner->GetActorEyesViewPoint(Eyelocation,EyeRotator);
	End=Eyelocation+(EyeRotator.Vector()*LineLength);
	
	
	//GetWorld()->LineTraceSingleByObjectType(Hit,Eyelocation,End,ObjectQueryParams);
	//bool HitBool=GetWorld()->LineTraceSingleByObjectType(Hit,Eyelocation,End,ObjectQueryParams);
	bool HitBool = GetWorld()->SweepMultiByObjectType(Hits,Eyelocation,End,FQuat::Identity,ObjectQueryParams,Shape);
	
	//GetWorld()->SweepMultiByObjectType(Hits,Eyelocation,End,FQuat::Identity,ObjectQueryParams,Shape);
    FColor hitcolor = HitBool?FColor::Green:FColor::Red;
	
	for(FHitResult Hit:Hits)
	{
		AActor*HitActor=Hit.GetActor();

		if(CVarDebugDrawInteraction.GetValueOnGameThread())
		{
			DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,hitcolor,false,2.0f);
		}
		if(HitActor)
		{
			if(HitActor->Implements<UGameplayInterface>())
			{
				APawn * MyPawn = Cast<APawn>(owner);
				IGameplayInterface::Execute_Interact(HitActor,MyPawn);
				DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,hitcolor,false,2.0f);
				break;
			}
		}
		
	}
	if(CVarDebugDrawInteraction.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(),Eyelocation,End,hitcolor,false,2.0f,0,2.0f);
	}
	
}