// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/LAction.h"
#include "Action_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API UAction_ProjectileAttack : public ULAction
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly,Category="Effect")
	UParticleSystem * ImpactVFx;

	UPROPERTY(EditAnywhere,Category="Socket")
	FName ShootSocket;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage * AttackAnim;

	UPROPERTY(EditDefaultsOnly,Category="Attack")
	float AttackAnimDelay;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* instigator);

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

	UAction_ProjectileAttack();
	
};
