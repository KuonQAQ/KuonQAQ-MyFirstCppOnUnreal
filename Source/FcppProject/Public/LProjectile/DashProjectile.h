// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LProjectile/ProjectileBase.h"
#include "DashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API ADashProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:

	ADashProjectile();
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DelayDetonate;

	void TeleportInstigator();

	virtual void Explode_Implementation() override;

	virtual  void BeginPlay() override;
	
};
