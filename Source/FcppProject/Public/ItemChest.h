// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class FCPPPROJECT_API AItemChest : public AActor,public IGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* instigatorpawn);
	
public:

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	// Sets default values for this actor's properties
	AItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent * LidMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
