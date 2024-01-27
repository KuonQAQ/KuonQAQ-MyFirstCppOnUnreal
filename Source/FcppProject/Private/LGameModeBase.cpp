// Fill out your copyright notice in the Description page of Project Settings.


#include "LGameModeBase.h"

#include "EngineUtils.h"
#include "LCharacter.h"
#include "LPlayerState.h"
#include "AI/AICharactor.h"
#include "EnvironmentQuery/EnvQueryManager.h"

static TAutoConsoleVariable<bool> ConsolseVarIsSpawnBot(TEXT("su.VarSpawnBot"),true,TEXT("IS Spawn Bot"),ECVF_Cheat);

ALGameModeBase::ALGameModeBase()
{
	SpawnTimerInterval = 2.0f;
	PlayerSpawnTime = 5.0f;
	KillCredit = 10;
}

void ALGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots,this,&ALGameModeBase::SpawnBotSpawnElapsed,SpawnTimerInterval,true);

	//生成PowerUp对象
	if(ensure(PowerUp.Num() > 0))
	{
		UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnPowerUpQuery, this, EEnvQueryRunMode::AllMatching, nullptr);
		if(ensure(QueryInstance))
		{
			QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ALGameModeBase::ALGameModeBase::OnPowerUpQueryComplete);
		}
	}
}



void ALGameModeBase::SpawnBotSpawnElapsed()
{
	if(!ConsolseVarIsSpawnBot.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disable via cvar 'CVarSpawnBots'."))
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper * QueryIntance=UEnvQueryManager::RunEQSQuery(this,SpawnBotQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);

	if(ensure(QueryIntance))
	{
		QueryIntance->GetOnQueryFinishedEvent().AddDynamic(this,&ALGameModeBase::OnQueryComplete);
	}
	
}



void ALGameModeBase::OnQueryComplete(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                     EEnvQueryStatus::Type QueryStatus)
{
    if(QueryStatus!=EEnvQueryStatus::Success)
    {
	    UE_LOG(LogTemp,Warning,TEXT("Spawn Bot EQS Query Failed"));
    	return;
    }

	int32 NumOfActiveBot = 0;

	for(TActorIterator<AAICharactor> It(GetWorld());It;++It)
	{
		AAICharactor * Bot = *It;

		UAttributeComponent * AttributeComponent = UAttributeComponent::GetAttribute(Bot);

		if(AttributeComponent&&AttributeComponent->IsActorActive())
		{
			NumOfActiveBot++;
		}
		
	}

	float MaxBotNum = 10.0f;
	
	if(DiffcultCurve)
	{
		MaxBotNum = DiffcultCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	
	if(NumOfActiveBot>=MaxBotNum)
	{
    		return;
	}
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if(Locations.Num()>0)
	{
		GetWorld()->SpawnActor<AActor>(EnemyClass,Locations[0],FRotator::ZeroRotator);
	}
}

void ALGameModeBase::OnPowerUpQueryComplete(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Powerup EQS Query Failed!"));
	}
	//环境查询得到的所有坐标
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	//要生成增益道具的所有坐标
	TArray<FVector> UseLocation;

	int32 SpawnCounter = 0;

	while(SpawnCounter < MaxPowerUpCount && Locations.Num() > 0)
	{
		//随机选取环境查询结果的一个坐标
		int32 RandomLocationIndex = FMath::RandRange(0, Locations.Num() - 1);
		FVector PickedLocation = Locations[RandomLocationIndex];
		//为了防止重复选取，将选取的坐标从数组中删掉
		Locations.RemoveAt(RandomLocationIndex);

		//随机选择一个Powerup进行生成
		int32 RandomClassIndex = FMath::RandRange(0, PowerUp.Num() - 1);
		TSubclassOf<APowerUpActor> RandomPowerupClass = PowerUp[RandomClassIndex];
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<APowerUpActor>(RandomPowerupClass, PickedLocation + FVector(0, 0, 50.f), FRotator::ZeroRotator, SpawnParams);
		SpawnCounter++;
	}
}

void ALGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ALCharacter * Player = Cast<ALCharacter>(VictimActor);
	if(Player)
	{
		FTimerHandle TimerHandle_DelayReSpawn;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"PlayerRepawnEvent",Player->GetController());

		GetWorldTimerManager().SetTimer(TimerHandle_DelayReSpawn,Delegate,PlayerSpawnTime,false);
	}

	APawn * killerPawn = Cast<APawn>(Killer);
	if(killerPawn)
	{
		ALPlayerState * PS = Cast<ALPlayerState>(killerPawn->GetPlayerState());
		if(PS)
		{
			PS->AddCredit(KillCredit);
		}
	}
	
}
void ALGameModeBase::killALL()
{
	for(TActorIterator<AAICharactor> It(GetWorld());It;++It)
	{
		AAICharactor * Bot = *It;

		UAttributeComponent * AttributeComponent = UAttributeComponent::GetAttribute(Bot);

		if(AttributeComponent&&AttributeComponent->IsActorActive())
		{
			AttributeComponent->Kill(this);
		}
	}
}

void ALGameModeBase::PlayerRepawnEvent(AController* controller)
{

	if(ensure(controller))
	{
		controller->UnPossess();
		RestartPlayer(controller);
	}
}
