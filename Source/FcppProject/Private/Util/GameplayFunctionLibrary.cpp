// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/GameplayFunctionLibrary.h"

#include "AttributeComponent.h"

bool UGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UAttributeComponent * AttributeComponent = UAttributeComponent::GetAttribute(TargetActor);
	if(AttributeComponent)
	{
		return AttributeComponent->ApplyHealthChange(DamageCauser,DamageAmount);
	}

	return  false;
}

bool UGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser,TargetActor,DamageAmount))
	{
		UPrimitiveComponent * Hitcomp= HitResult.GetComponent();
		if(Hitcomp&&Hitcomp->IsSimulatingPhysics(HitResult.BoneName))
		{
			Hitcomp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.0f,HitResult.ImpactPoint,HitResult.BoneName);
		}
		return true;
	}
	return false;
}
