// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LAction.h"
#include "Components/ActorComponent.h"
#include "LActionComponent.generated.h"


class ULAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FCPPPROJECT_API ULActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULActionComponent();

	UFUNCTION(BlueprintCallable,Category="Action")
	void AddAction(TSubclassOf<ULAction> ActionClass);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StartActionByName(AActor* instigator,FName ActionName);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StopActionByName(AActor* instigator,FName ActionName);

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ULAction>> DefaultAction;

protected:
	
	UPROPERTY()
	TArray<ULAction*> Actions;

	
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
