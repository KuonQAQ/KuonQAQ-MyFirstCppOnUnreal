// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_LowHealth.h"

#include "AttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_LowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp=OwnerComp.GetBlackboardComponent();
	AActor * AI = Cast<AActor>(BlackboardComp->GetValueAsObject("SelfActor"));

	if(AI)
	{
		UAttributeComponent* AttributeComponent= Cast<UAttributeComponent>(AI->GetComponentByClass(UAttributeComponent::StaticClass()));

		if(ensureMsgf(AttributeComponent,TEXT("AI Hasnt Attritubecomp")))
		{
			bool isLowHealth = AttributeComponent->Health<= AttributeComponent->GetheathMax()*0.4f;

			BlackboardComp->SetValueAsBool(LowHealth.SelectedKeyName,isLowHealth);
		}
	}
}
