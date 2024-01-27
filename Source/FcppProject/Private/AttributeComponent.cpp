// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

#include "LGameModeBase.h"


static TAutoConsoleVariable<float> GalDamageMultiplier(TEXT("su.galdamagemultiplier"),1.0f,TEXT("全局伤害乘数"),ECVF_Cheat);
// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	MaxHealth=100.0f;
	Health=MaxHealth;
	
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}




bool UAttributeComponent::IsActorActive() const
{
	return Health > 0.0f;
}

bool UAttributeComponent::Kill(AActor* interghtor)
{
	return ApplyHealthChange(interghtor,-GetheathMax());
}

bool UAttributeComponent::IsFullHeath()
{
	return Health == MaxHealth;
}

float UAttributeComponent::GetheathMax()
{
	return MaxHealth;
}

void UAttributeComponent::SetHealthToMax()
{
	if(!IsFullHeath())
	{
		Health = GetheathMax();
		OnHealthChanged.Broadcast(nullptr,this,Health,0);
	}
}

bool UAttributeComponent::ApplyHealthChange(AActor* instigatoractor,float Delat)
{

	if(!GetOwner()->CanBeDamaged()&&Delat<0.0f)
	{
		return false;
	}

	if(Delat<0.0f)
	{
		float damagemultip = GalDamageMultiplier.GetValueOnGameThread();
		
		Delat*=damagemultip;
	}
	float oldheath = Health;
	
	//Health=Health+(Delat);
	Health=FMath::Clamp(Health+Delat,0.0f,MaxHealth);

	float Actualhealth = Health - oldheath;
	
	OnHealthChanged.Broadcast(instigatoractor,this,Health,Actualhealth);

	//Died
	if(Actualhealth<0.0f&&Health==0)
	{
		ALGameModeBase *GM = GetWorld()->GetAuthGameMode<ALGameModeBase>();

		if(GM)
		{
			GM->OnActorKilled(GetOwner(),instigatoractor);
		}
	}
	
	return Actualhealth !=0;
}

UAttributeComponent* UAttributeComponent::GetAttribute(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<UAttributeComponent>(FromActor->GetComponentByClass(UAttributeComponent::StaticClass()));
	}

	return nullptr;
}