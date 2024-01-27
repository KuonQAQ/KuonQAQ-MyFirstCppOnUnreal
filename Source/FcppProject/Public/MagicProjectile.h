// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MagicProjectile.generated.h"

UCLASS()
class FCPPPROJECT_API AMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UFUNCTION()
	void OnAtorOverlap( UPrimitiveComponent* OverlappedComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent * SphereComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent * ParticleSysComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent * ProjectileMovement;

	UPROPERTY(EditAnywhere,Category="Audio")
	UAudioComponent * FlightSound;

	UPROPERTY(EditAnywhere,Category="Audio")
	UAudioComponent * ImpactSound;

	UPROPERTY(EditAnywhere,Category="Damage")
	float Damage;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
