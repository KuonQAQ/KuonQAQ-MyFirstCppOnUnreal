// Fill out your copyright notice in the Description page of Project Settings.


#include "LProjectile/ProjectileBase.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this,&AProjectileBase::OnActorHit);
	RootComponent = SphereComp;

	ParticleSysComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleSysComp->SetupAttachment(RootComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->bRotationFollowsVelocity =true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 8000;
}

void AProjectileBase::Explode_Implementation()
{
	if(ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVFx,GetActorLocation(),GetActorRotation());

		Destroy();
	}
}

void AProjectileBase::OnActorHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	Explode();
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



