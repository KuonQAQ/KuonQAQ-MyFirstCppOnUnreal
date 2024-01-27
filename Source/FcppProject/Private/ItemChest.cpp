// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemChest.h"



// Sets default values
AItemChest::AItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Basemesh"));
	RootComponent=BaseMesh;

	LidMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch=100.0f;

}

// Called when the game starts or when spawned
void AItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemChest::Interact_Implementation(APawn* instigatorpawn)
{
	 LidMesh->SetRelativeRotation(FRotator(TargetPitch,0,0));
}