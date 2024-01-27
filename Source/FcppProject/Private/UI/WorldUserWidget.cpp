// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WorldUserWidget.h"

#include "AttributeComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if(!IsValid(AttachActor))
	{
		RemoveFromParent();
		return;
	}
    FVector2D ScreenPostition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),AttachActor->GetActorLocation(),ScreenPostition))
	{
		float scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPostition/=scale;

		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPostition);
		}
	}

	
}
