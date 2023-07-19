// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TPS_LabyrinthGameModeBase.h"
#include "Enums.h"
#include "SaveActorNameAndTransform.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API USaveActorNameAndTransform : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<FSaveData> patrolPointActorsData;
	UPROPERTY()
		TArray<FSaveData> enemyActorsData;
	UPROPERTY()
		TArray<FSaveData> chestActorsData;
	
	bool SavePatrolPointActor(class APatrolPoint* pp);
	bool SaveEnemyActor(class AEnemy* enemy);
	bool SaveChestActor(class AChest* chest);
};
