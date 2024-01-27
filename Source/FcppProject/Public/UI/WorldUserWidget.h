// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "WorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FCPPPROJECT_API UWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentSizeBox;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	AActor * AttachActor;
	
};
