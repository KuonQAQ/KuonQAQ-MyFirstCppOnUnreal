// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpActor.h"
#include "PowerUp_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API APowerUp_HealthPotion : public APowerUpActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent * StaticComp;

	UPROPERTY(EditAnywhere)
	int32 CreditCoat;

public:

	APowerUp_HealthPotion();

	void Interact_Implementation(APawn* instigatorpawn) override;
	
};
