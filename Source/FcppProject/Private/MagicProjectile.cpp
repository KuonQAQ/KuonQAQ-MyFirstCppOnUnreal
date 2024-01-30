// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"

#include "AttributeComponent.h"
#include "Components/AudioComponent.h"
#include "GAS/LActionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Util/GameplayFunctionLibrary.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AMagicProjectile::OnAtorOverlap);
	
	SphereComp->SetCollisionProfileName("Projectile");

	ParticleSysComp = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	ParticleSysComp->SetupAttachment(SphereComp);

	FlightSound = CreateDefaultSubobject<UAudioComponent>("FlightSound");
	FlightSound->SetupAttachment(RootComponent);
	
	ImpactSound = CreateDefaultSubobject<UAudioComponent>("ImpactSound");
	ImpactSound->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;

	
}

void AMagicProjectile::OnAtorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor!= GetInstigator())
	{

		ULActionComponent* ActionComponent = Cast<ULActionComponent>(OtherActor->GetComponentByClass(ULActionComponent::StaticClass()));
		if(ActionComponent&&ActionComponent->ActiveGameplayTags.HasTag(ParryTag))
		{
			ProjectileMovement->Velocity=-ProjectileMovement->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		//UAttributeComponent * AttributeComponent= Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
		UGameplayStatics::PlayWorldCameraShake(this,CameraShake,GetActorLocation(),100,4000);
		
			if(UGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(),OtherActor,Damage,SweepResult))
			{
				//AttributeComponent->ApplyHealthChange(GetInstigator(),Damage);
				UGameplayStatics::PlaySoundAtLocation(this, ImpactSound->Sound, GetActorLocation(), GetActorRotation(), 1, 1, 0, nullptr, nullptr, nullptr); 
				Destroy();
			}
		
	}
	
}


// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

