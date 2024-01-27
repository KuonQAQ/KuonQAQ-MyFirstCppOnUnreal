// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummy.h"

// Sets default values
ATargetDummy::ATargetDummy()
{

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComponent;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("Attributecomp");

	AttributeComponent->OnHealthChanged.AddDynamic(this,&ATargetDummy::OnheathChange);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetDummy::OnheathChange(AActor* instigatorActor, UAttributeComponent* owningComp, float newheath, float delta)
{
	if(delta < 0)
	{
		StaticMeshComponent->SetScalarParameterValueOnMaterials("Hitontime",GetWorld()->TimeSeconds);
	}
	
}

// Called every frame
void ATargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

