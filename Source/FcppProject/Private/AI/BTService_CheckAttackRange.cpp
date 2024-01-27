// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp=OwnerComp.GetBlackboardComponent();

	if(ensure(BlackboardComp))
	{
		AActor * Myactor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if(Myactor)
		{
			AAIController * MyController = OwnerComp.GetAIOwner();

			if(MyController)
			{
				APawn* AiPawn=MyController->GetPawn();

				if(AiPawn)
				{
					float Distance= FVector::Distance(Myactor->GetActorLocation(),AiPawn->GetActorLocation());

					//UE_LOG(LogTemp,Warning,TEXT("DIstance: %s"),Distance);
					
					bool BWithinRange = Distance < 2000.0f;
					
                    bool BHasLookPlayer = false ;
					if(BWithinRange)
					{
						BHasLookPlayer = MyController->LineOfSightTo(Myactor);
					}

					BlackboardComp->SetValueAsBool(CheackAttackRange.SelectedKeyName,BWithinRange&&BHasLookPlayer);
				}
			}
		}
	}
}
