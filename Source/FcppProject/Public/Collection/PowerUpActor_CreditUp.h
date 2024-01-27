// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpActor.h"
#include "PowerUpActor_CreditUp.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API APowerUpActor_CreditUp : public APowerUpActor
{
	GENERATED_BODY()

public:
	APowerUpActor_CreditUp();

	virtual void Interact_Implementation(APawn* instigatorpawn) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditsValue;
};
