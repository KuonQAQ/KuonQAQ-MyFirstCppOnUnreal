// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "UI/WorldUserWidget.h"
#include "AICharactor.generated.h"

UCLASS()
class FCPPPROJECT_API AAICharactor : public ACharacter
{
	GENERATED_BODY()

public:


	
	AAICharactor();

protected:
	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UWorldUserWidget> HealthBar;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	UWorldUserWidget * ActiveUserwidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent * UpawnSensingComp;

	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	UAttributeComponent * AttributeComponent;
	
	UFUNCTION()
	void SensePawn(APawn* Pawn);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnheathChange(AActor * instigatorActor, UAttributeComponent* owningComp,float newheath,float delta);

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);

	
};
