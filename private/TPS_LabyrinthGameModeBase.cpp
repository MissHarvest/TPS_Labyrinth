// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPS_LabyrinthGameModeBase.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "EditCamera.h"
#include "Chest.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include "SaveActorNameAndTransform.h"
#include <Blueprint/UserWidget.h>
#include <TitleWidget.h>
#include "PauseGameWidget.h"
#include "PatrolPoint.h"
#include "UIManager.h"
#include "UISubSystem.h"
ATPS_LabyrinthGameModeBase::ATPS_LabyrinthGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATPS_LabyrinthGameModeBase::BeginPlay()
{
	// GameState
	Super::BeginPlay();
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (LoadGame() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Game"));
		return;
	}
	switch (entermode)
	{
	case EEnterType::Edit:
	{
		if (editCamFactory == nullptr) return;
		FTransform t(FVector(3000, 300, 2000));
		editCamera = GetWorld()->SpawnActor<AEditCamera>(editCamFactory, t);
		playerController->SetViewTargetWithBlend(editCamera);
		playerController->SetShowMouseCursor(true);

		if (editWidget == nullptr) return;
		editUI = CreateWidget(GetWorld(), editWidget);
		editUI->AddToViewport();
	}
		break;
	case EEnterType::Normal:
	{
		EnableInput(playerController);
		if (InputComponent)
		{
			InputComponent->BindAction("Pause", IE_Pressed, this, &ATPS_LabyrinthGameModeBase::TogglePauseUI);
		}		
		UUISubSystem* sub = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UUISubSystem>();
		if (sub)
		{
			UE_LOG(LogTemp, Warning, TEXT("sub valid"));
			sub->ShowUI("DefaultGame");
		}
	}
		break;
	}
	
}

void ATPS_LabyrinthGameModeBase::TogglePauseUI()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	playerController->SetShowMouseCursor(true);
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ShowUI("PauseGame");
}

void ATPS_LabyrinthGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	escapeTimer += DeltaTime;
}

APatrolPoint* ATPS_LabyrinthGameModeBase::CreatePatrolPoint(FTransform transform, FString name)
{
	auto actor = GetWorld()->SpawnActor<APatrolPoint>(patrolFactory, transform); // APatrolPoint
	if (actor == nullptr) return nullptr;
	actor->name = name;
#if WITH_EDITOR
	actor->SetActorLabel(name);
#endif	
	objects.Add(actor);
	return actor;
}

bool ATPS_LabyrinthGameModeBase::CreateEnemy(FTransform transform)
{
	auto enemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory, transform);
	if (enemy == nullptr) return false;
	FString name = FString::Printf(TEXT("Enemy%2d"), enemys.Num() + 1);
#if WITH_EDITOR
	enemy->SetActorLabel(name);
#endif
	enemy->name = name;
	enemy->fsm->FindPatrolPoint();
	enemys.Add(enemy);
	selectedActor = Cast<AActor>(enemy);	
	return true;
}

void ATPS_LabyrinthGameModeBase::CreateChest(FTransform transform)
{
	auto chest = GetWorld()->SpawnActor<AChest>(chestFactory, transform);
	if (chest == nullptr) return;
	selectedActor = Cast<AActor>(chest);
	chests.Add(chest);
}

bool ATPS_LabyrinthGameModeBase::SaveActors()
{
	if (saveActorFactory == nullptr) return false;
	
	auto saveGameTemp = UGameplayStatics::CreateSaveGameObject(saveActorFactory);
	if (saveGameTemp == nullptr) return false;

	auto saveGame = Cast<USaveActorNameAndTransform>(saveGameTemp);
	
	for (auto chest : chests)
	{
		saveGame->SaveChestActor(chest);
	}
	for (auto actor : objects)
	{
		saveGame->SavePatrolPointActor(actor);
	}
	for (auto enemy : enemys)
	{
		saveGame->SaveEnemyActor(enemy);
	}
	if (UGameplayStatics::SaveGameToSlot(saveGame, TEXT("objects"), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Actors Finished"));
		return true;
	}
	return false;
}

void ATPS_LabyrinthGameModeBase::SetViewTarget(AActor* target, bool showMouse)
{
	auto _controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	_controller->SetViewTargetWithBlend(target);
	_controller->SetShowMouseCursor(true);
}

bool ATPS_LabyrinthGameModeBase::LoadGame()
{
	UE_LOG(LogTemp, Warning, TEXT("ATPS_LabyrinthGameModeBase StartPlay"));
	if (UGameplayStatics::DoesSaveGameExist("objects", 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Objects Slot Exist"));
		auto slot = UGameplayStatics::LoadGameFromSlot("objects", 0);
		if (slot == nullptr) return false;
		auto saveGameSlot = Cast<USaveActorNameAndTransform>(slot);
		if (saveGameSlot == nullptr) return false;
		auto _pps = saveGameSlot->patrolPointActorsData;
		for (auto pp : _pps)
		{
			CreatePatrolPoint(pp.transform, pp.name);
		}
		UE_LOG(LogTemp, Warning, TEXT("Create PP Finished"));

		auto _chests = saveGameSlot->chestActorsData;
		for (auto chest : _chests)
		{
			CreateChest(chest.transform);
		}
		UE_LOG(LogTemp, Warning, TEXT("Create Chest Finished"));

		auto _enemys = saveGameSlot->enemyActorsData;
		for (auto enemy : _enemys)
		{
			CreateEnemy(enemy.transform);
		}
		selectedActor = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Create Enemy Finished"));
	}
	return true;
}