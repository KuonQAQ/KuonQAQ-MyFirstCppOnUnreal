// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp_HealthPotion.h"

#include "AttributeComponent.h"
#include "LCharacter.h"
#include "LPlayerState.h"

APowerUp_HealthPotion::APowerUp_HealthPotion()
{
	StaticComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticmeshComp");
	StaticComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticComp->SetupAttachment(RootComponent);

	CreditCoat=50;
}

void APowerUp_HealthPotion::Interact_Implementation(APawn* instigatorpawn)
{
	ALCharacter* MyCharactor = Cast<ALCharacter>(instigatorpawn);
	
	if(!ensure(instigatorpawn))
	{
		return;
	}

	UAttributeComponent * AttributeComponent = Cast<UAttributeComponent>(MyCharactor->GetComponentByClass(UAttributeComponent::StaticClass()));

	if(ensure(AttributeComponent)&&!AttributeComponent->IsFullHeath())
	{
		if(ALPlayerState * PS = Cast<ALPlayerState>(MyCharactor->GetPlayerState()))
		{
			if(PS->RemoveCredit(CreditCoat)&&AttributeComponent->ApplyHealthChange(this,AttributeComponent->GetheathMax()))
			{
				HideAndCooldownPowerup();
			}
		}
	}
}
