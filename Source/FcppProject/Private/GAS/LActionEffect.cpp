// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/LActionEffect.h"

ULActionEffect::ULActionEffect()
{
	BAutoStart=true;
}

void ULActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	//启动计时器
	if(Duration > 0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}

	if(Period > 0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodEffect", Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}
}

void ULActionEffect::StopAction_Implementation(AActor* Instigator)
{
	//检查周期效果是否会同时触发，如果时间近乎一样，那么先触发周期效果，再停止Action
	if(GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodEffect(Instigator);
	}
	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	ULActionComponent* Comp = GetOwingComponent();
	if(Comp)
	{
		Comp->RemoveAction(this);
	}
}

void ULActionEffect::ExecutePeriodEffect_Implementation(AActor* Instigator)
{
}

