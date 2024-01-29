// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Action_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UAction_ProjectileAttack::UAction_ProjectileAttack()
{
	ShootSocket = "Muzzle_01";
	AttackAnimDelay = 0.1f;
}
void UAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* instigator)
{
	if(ensureAlways(ProjectileClass))
	{
		FVector Handlocation = instigator->GetMesh()->GetSocketLocation(ShootSocket);

		FVector TraceStart = instigator->GetPawnViewLocation();
		FVector TraceEnd = TraceStart+(instigator->GetControlRotation().Vector()*5000);

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(instigator);

		FCollisionObjectQueryParams objparams;
		objparams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objparams.AddObjectTypesToQuery(ECC_WorldStatic);
		objparams.AddObjectTypesToQuery(ECC_Pawn);

		FHitResult HitResult;

		if(GetWorld()->SweepSingleByObjectType(HitResult,TraceStart,TraceEnd,FQuat::Identity,objparams,Shape,Params))
		{
			TraceEnd=HitResult.ImpactPoint;
		}

		FRotator ProjectileRotator = FRotationMatrix::MakeFromX(TraceEnd-Handlocation).Rotator();
		
		FTransform SpawnTrans = FTransform(ProjectileRotator,Handlocation);

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.Instigator= instigator;
	
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTrans,SpawnParam);
	}

	StopAction(instigator);
	
}

void UAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter * Character=Cast<ACharacter>(Instigator);

	if(Character)
	{
		Character->PlayAnimMontage(AttackAnim);
		
		UGameplayStatics::SpawnEmitterAttached(ImpactVFx,Character->GetMesh(),ShootSocket,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"AttackDelay_Elapsed",Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay,Delegate,AttackAnimDelay,false);

		
	}
}


