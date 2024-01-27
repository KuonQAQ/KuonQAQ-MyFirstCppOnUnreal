// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PowerUpActor.generated.h"

UCLASS()
class FCPPPROJECT_API APowerUpActor : public AActor,public IGameplayInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere,Category="PowerUP")
	float Respawntime;

	FTimerHandle TimerHandle_Respawntimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerUpState(bool BNewIsActive);

	UPROPERTY(VisibleAnywhere,Category="sphere comp")
	USphereComponent * SphereComp;
	
	
public:	
	// Sets default values for this actor's properties
	APowerUpActor();

	void Interact_Implementation(APawn* instigatorpawn) override;



};
