// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FCPPPROJECT_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Attributes")
	float MaxHealth;
	// Sets default values for this component's properties
	UAttributeComponent();

protected:

	
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	bool IsActorActive() const;

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor * interghtor);

	UFUNCTION(BlueprintCallable)
	bool IsFullHeath();

	UFUNCTION(BlueprintCallable)
	float GetheathMax();

	UFUNCTION(BlueprintCallable)
	void SetHealthToMax();

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* instigatoractor, float Delat);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category="Attribute")
	static UAttributeComponent * GetAttribute(AActor * FromActor);

		
};
