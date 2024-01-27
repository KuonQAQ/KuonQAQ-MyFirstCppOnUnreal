// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

UCLASS(Abstract)
class FCPPPROJECT_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:

	UPROPERTY(EditDefaultsOnly,Category="Effect")
	UParticleSystem * ImpactVFx;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent * SphereComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent * ParticleSysComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent * ProjectileMovement;

	UFUNCTION()
	virtual void OnActorHit( UPrimitiveComponent* OverlappedComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & HitResult);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

public:	
	
};
