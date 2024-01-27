// Fill out your copyright notice in the Description page of Project Settings.


#include "Collection/PowerUpActor_CreditUp.h"

#include "LCharacter.h"
#include "LPlayerState.h"

APowerUpActor_CreditUp::APowerUpActor_CreditUp()
{
	CreditsValue = 10;
}

void APowerUpActor_CreditUp::Interact_Implementation(APawn* instigatorpawn)
{
	ALCharacter* MyCharactor = Cast<ALCharacter>(instigatorpawn);
	
	if(!ensure(instigatorpawn))
	{
		return;
	}
	
	if(ALPlayerState * PlayerState=Cast<ALPlayerState>(MyCharactor->GetPlayerState()))
	{
		if(PlayerState->AddCredit(CreditsValue))
		{
			HideAndCooldownPowerup();
		}
	}
}
