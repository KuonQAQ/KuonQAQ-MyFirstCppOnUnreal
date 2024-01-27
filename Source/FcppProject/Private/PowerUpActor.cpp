// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpActor.h"



// Sets default values
APowerUpActor::APowerUpActor()
{
 	SphereComp = CreateDefaultSubobject<USphereComponent>("Spherecomp");
	SphereComp->SetCollisionProfileName("PowerUp");

	RootComponent=SphereComp;

	Respawntime = 10.0f;

}


void APowerUpActor::ShowPowerup()
{
	SetPowerUpState(true);
}

void APowerUpActor::HideAndCooldownPowerup()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_Respawntimer,this,&APowerUpActor::ShowPowerup,Respawntime);
}

void APowerUpActor::SetPowerUpState(bool BNewIsActive)
{
	SetActorEnableCollision(BNewIsActive);

	RootComponent->SetVisibility(BNewIsActive,true);
}

void APowerUpActor::Interact_Implementation(APawn* instigatorpawn)
{
	//IGameplayInterface::Interact_Implementation(instigatorpawn);
}
