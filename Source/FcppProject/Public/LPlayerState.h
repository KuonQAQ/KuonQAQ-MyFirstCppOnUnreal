// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditChange,ALPlayerState*,LPlayerState,int32,NewCredit,int32,delta);
/**
 * 
 */
UCLASS()
class FCPPPROJECT_API ALPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly,Category="Credit")
	int32 Credit;

public:
	UFUNCTION(BlueprintCallable,Category="Credit")
	int32 GetCredit() const;

	UFUNCTION(BlueprintCallable,Category="Credit")
	bool AddCredit(int32 delta);

	UFUNCTION(BlueprintCallable,Category="Credit")
	bool RemoveCredit(int32 delta);


	UPROPERTY(BlueprintAssignable,Category="Event")
	FOnCreditChange OnCreditChange;
};
