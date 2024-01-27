// Fill out your copyright notice in the Description page of Project Settings.


#include "LPlayerState.h"

int32 ALPlayerState::GetCredit() const
{
	return Credit;
}

bool ALPlayerState::AddCredit(int32 delta)
{
	if(!ensure(delta >= 0))
	{
		return false;
	}
	Credit += delta;
	OnCreditChange.Broadcast(this,Credit,delta);
	return true;
}

bool ALPlayerState::RemoveCredit(int32 delta)
{
	if(!ensure(delta >= 0))
	{
		return false;
	}

	if(Credit<delta)
	{
		return false;
	}

	Credit-=delta;
	OnCreditChange.Broadcast(this,Credit,delta);
	return true;
}
