// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveActorNameAndTransform.h"
#include "TPS_LabyrinthGameModeBase.h"
#include "PatrolPoint.h"
#include "Enemy.h"
#include "Chest.h"
#include "PatrolPoint.h"
bool USaveActorNameAndTransform::SavePatrolPointActor(APatrolPoint* pp)
{
	if (pp == nullptr) return false;
	//FString name = pp->GetActorLabel();//pp->GetActorTransform();
	FString name = pp->name;
	FTransform transform = pp->GetActorTransform();
	FSaveData saveData;
	saveData.transform = transform;
	saveData.name = name;
	patrolPointActorsData.Add(saveData);
	return true;
}

bool USaveActorNameAndTransform::SaveEnemyActor(AEnemy* enemy)
{
	if (enemy == nullptr) return false;
	UE_LOG(LogTemp, Warning, TEXT("Save Enemy Actor : enemy is not null"));
	//FString name = enemy->GetActorLabel();//pp->GetActorTransform();
	FString name = enemy->name;
	FTransform transform = enemy->GetActorTransform();
	FSaveData saveData;// = nullptr;
	saveData.transform = transform;
	saveData.name = name;
	enemyActorsData.Add(saveData);
	return true;
}

bool USaveActorNameAndTransform::SaveChestActor(AChest* chest)
{
	if (chest == nullptr) return false;
	//FString name = chest->GetActorLabel();//pp->GetActorTransform();
	FString name = "Chest";
	FTransform transform = chest->GetActorTransform();
	FSaveData saveData;
	saveData.transform = transform;
	saveData.name = name;
	chestActorsData.Add(saveData);
	return true;
}