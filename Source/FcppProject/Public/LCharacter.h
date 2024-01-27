// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "InteractComponent.h"
#include "GameFramework/Character.h"
#include "LCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class FCPPPROJECT_API ALCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALCharacter();
	
	

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlackHoleProjectile;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DashProjectile;

	UPROPERTY(EditDefaultsOnly,Category="Effect")
	UParticleSystem * ImpactVFx;

protected:

	UPROPERTY(EditAnywhere,Category="Socket")
	FName ShootSocket;
	
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UInteractComponent* InteractComponent;
	
    UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAttributeComponent * AttributeComp;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage * AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	
	FTimerHandle TimerHandle_BlackHoleAttack;

	FTimerHandle TimerHandle_TeleportSkill;


	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float value);

	void PrimartAttack();
	
	void BlackHoleAttack();

	void TeleportSkill();

	void Jump();

	void PrimaryInteract();

	void TimerHandle_PrimaryAttackEvent();
	
	void TimerHandle_BlackHoleAttackEvent();

	void Timehandle_TeleportSkillEvent();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	UFUNCTION()
	void OnheathChange(AActor * instigatorActor, UAttributeComponent* owningComp,float newheath,float delta);

	virtual void PostInitializeComponents() override;

	UFUNCTION(Exec)
	void HealSelf(float count = 100);

	virtual FVector GetPawnViewLocation() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	

};