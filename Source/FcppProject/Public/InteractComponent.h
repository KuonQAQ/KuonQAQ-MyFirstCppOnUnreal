// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/WorldUserWidget.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FCPPPROJECT_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float LineLength;
	// Sets default values for this component's properties
	UInteractComponent();

	void PrimaryInteract();
	
	void FindBestInteractable();
	
protected:

	//当前可交互的物体
	UPROPERTY() //将其标记为UPEOPERTY, 监控其生命周期，避免空悬指针的发生
	AActor* FocusActor;

	//指定生成控件的类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWorldUserWidget> DefaultWidgetClass;

	//当有可交互的物体时，会生成指定的控件
	UPROPERTY()
	UWorldUserWidget* DefaultWidgetInstance;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
