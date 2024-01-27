// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharactor.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICharactor::AAICharactor()
{
 	
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("Attributecomp");
	
	UpawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("UPawnSensingcomp");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AAICharactor::SensePawn(APawn* Pawn)
{
	SetTargetActor(Pawn);
}

void AAICharactor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UpawnSensingComp->OnSeePawn.AddDynamic(this,&AAICharactor::SensePawn);
	AttributeComponent->OnHealthChanged.AddDynamic(this,&AAICharactor::OnheathChange);
}

void AAICharactor::OnheathChange(AActor* instigatorActor, UAttributeComponent* owningComp, float newheath, float delta)
{

	if(delta<0)
	{

        SetTargetActor(instigatorActor);
		
        ActiveUserwidget= CreateWidget<UWorldUserWidget>(GetWorld(),HealthBar);
		if(ActiveUserwidget)
		{
			ActiveUserwidget->AttachActor = this;
			ActiveUserwidget->AddToViewport();
		}
		
		
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);

		if(newheath<=0)
		{
			AAIController *AIC = Cast<AAIController>(GetController());
			if(AIC)
			{
				AIC->GetBrainComponent()->StopLogic("killed");
			}

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			SetLifeSpan(10.0f);
		}
	}
}

void AAICharactor::SetTargetActor(AActor* NewTarget)
{
	AAIController * AIC = Cast<AAIController>(GetController());
	if(AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor",NewTarget);

		DrawDebugString(GetWorld(),GetActorLocation(),"Player SPoTTED",nullptr,FColor::White,4.0f,true);
	}
}

// Called when the game starts or when spawned



