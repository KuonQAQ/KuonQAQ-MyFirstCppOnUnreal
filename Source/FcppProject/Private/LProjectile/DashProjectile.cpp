// Fill out your copyright notice in the Description page of Project Settings.


#include "LProjectile/DashProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ADashProjectile::ADashProjectile()
{
	TeleportDelay = 0.3f;
	DetonateDelay = 0.3f;

	ProjectileMovement->InitialSpeed = 6000.f;
}

void ADashProjectile::TeleportInstigator()
{
	AActor * ActorTeleport = GetInstigator();

	if(ensure(ActorTeleport))
	{
		ActorTeleport->TeleportTo(GetActorLocation(),ActorTeleport->GetActorRotation(),false,false);
	}

	Destroy();
}

void ADashProjectile::Explode_Implementation()
{
	//Super::Explode_Implementation();
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVFx,GetActorLocation(),GetActorRotation());

	ParticleSysComp->DeactivateSystem();
	ProjectileMovement->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayTeleport;

	GetWorldTimerManager().SetTimer(TimerHandle_DelayTeleport,this,&ADashProjectile::TeleportInstigator,TeleportDelay);
	
}

void ADashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayDetonate,this,&ADashProjectile::Explode,DetonateDelay);
}
