// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "Framework/Docking/LayoutExtender.h"
#include "GameFramework/Actor.h"
#include "TargetDummy.generated.h"

UCLASS()
class FCPPPROJECT_API ATargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetDummy();

protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent * StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UAttributeComponent * AttributeComponent;

	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnheathChange(AActor * instigatorActor, UAttributeComponent* owningComp,float newheath,float delta);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
