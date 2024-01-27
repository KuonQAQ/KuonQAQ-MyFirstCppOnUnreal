// Fill out your copyright notice in the Description page of Project Settings.


#include "CppExploreBarrel.h"

#include "DrawDebugHelpers.h"

// Sets default values
ACppExploreBarrel::ACppExploreBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// UE中的“模拟物理”选项
	MeshComp->SetSimulatePhysics(true);
	// 等同于在UE中将“碰撞预设”设置为“PhysicsActor”
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius = 750.0f;			 // 爆炸范围
	ForceComp->ImpulseStrength = 700.0f; // 冲击力
	ForceComp->bImpulseVelChange = true; // 忽略质量大小；见UE中ForceComp的“冲量速度变更” 

}

void ACppExploreBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this,&ACppExploreBarrel::OnActorHit);
}

void ACppExploreBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	UE_LOG(LogTemp,Warning,TEXT("OtherActor : %s, gametime:%f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);

	FString CombineLog = FString::Printf(TEXT("Hit at location: %s"),*Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(),Hit.ImpactPoint,CombineLog,nullptr,FColor::Green,1.0f,true);
}

// Called when the game starts or when spawned
void ACppExploreBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppExploreBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

