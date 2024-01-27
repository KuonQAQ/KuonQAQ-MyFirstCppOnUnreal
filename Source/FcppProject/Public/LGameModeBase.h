// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpActor.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "LGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API ALGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALGameModeBase();
	
	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor * VictimActor ,AActor * Killer);

protected:

	UPROPERTY(EditDefaultsOnly,Category="AI")
	TSubclassOf<AActor> EnemyClass;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly,Category="AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly,Category="Player")
	float PlayerSpawnTime;

	UPROPERTY(EditDefaultsOnly,Category="AI")
	UCurveFloat * DiffcultCurve;

	UPROPERTY(EditDefaultsOnly,Category="Credit")
	int32 KillCredit;

	UPROPERTY(EditDefaultsOnly,Category="PowerUp")
	TArray<TSubclassOf<APowerUpActor>> PowerUp;
	

	UPROPERTY(EditDefaultsOnly,Category="PowerUp")
	int32 MaxPowerUpCount;
	
	UPROPERTY(EditDefaultsOnly)
	UEnvQuery * SpawnPowerUpQuery;
	
	
	UPROPERTY(EditDefaultsOnly)
    UEnvQuery * SpawnBotQuery;
	
	UFUNCTION()
	void SpawnBotSpawnElapsed();

	UFUNCTION(Exec)
	void killALL();

	UFUNCTION()
	void PlayerRepawnEvent(AController * controller);
	
	UFUNCTION()
	void OnQueryComplete(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
	UFUNCTION()
	void OnPowerUpQueryComplete(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
	
};

