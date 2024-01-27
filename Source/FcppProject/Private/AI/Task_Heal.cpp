// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task_Heal.h"

#include "AIController.h"
#include "AttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController= OwnerComp.GetAIOwner();
	
	UBlackboardComponent* BlackboardComp=OwnerComp.GetBlackboardComponent();
	AActor * AI = Cast<AActor>(BlackboardComp->GetValueAsObject("SelfActor"));

	if(AI)
	{
		UAttributeComponent* AttributeComponent= Cast<UAttributeComponent>(AI->GetComponentByClass(UAttributeComponent::StaticClass()));

		if(ensureMsgf(AttributeComponent,TEXT("AI Hasnt Attritubecomp")))
		{
			AttributeComponent->SetHealthToMax();

			
		}
	}
	return EBTNodeResult::Succeeded;
}
