// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task_AttackRange.h"

#include "AIController.h"
#include "AttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"


UTask_AttackRange::UTask_AttackRange()
{
	AttackCD = 2.0f;
	MaxBulletSpread= 2.0f;
}

EBTNodeResult::Type UTask_AttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController= OwnerComp.GetAIOwner();
	if(AIController)
	{
		ACharacter * Mypawn = Cast<ACharacter>(AIController->GetPawn());
		if(Mypawn==nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector ShootPoint = Mypawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor * Myactor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

		if(Myactor==nullptr)
		{
			return EBTNodeResult::Failed;
		}

		UAttributeComponent * AttributeComponent = UAttributeComponent::GetAttribute(Myactor);

		if(!AttributeComponent->IsActorActive())
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = Myactor->GetActorLocation()-ShootPoint;

		FRotator MuzzleRot = Direction.Rotation();

		MuzzleRot.Pitch+= FMath::RandRange(-MaxBulletSpread,MaxBulletSpread);
		MuzzleRot.Yaw += FMath::RandRange(-MaxBulletSpread,MaxBulletSpread);

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.Instigator = Mypawn;
	
		AActor * ProjectileActor =GetWorld()->SpawnActor<AActor>(ProjectileClass,ShootPoint,MuzzleRot,SpawnParam);

		

		return ProjectileActor?EBTNodeResult::Succeeded:EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
