// Fill out your copyright notice in the Description page of Project

#include "EnemyEditWidget.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetStringLibrary.h>
#include "TPS_LabyrinthGameModeBase.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "PatrolPoint.h"
void UEnemyEditWidget::NativeConstruct()
{
	btn_CreatePoint->OnClicked.Clear();
	btn_CreatePoint->OnClicked.AddDynamic(this, &UEnemyEditWidget::ClickCreatePointBtn);
}

void UEnemyEditWidget::ClickCreatePointBtn()
{
	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode == nullptr) return;
	FTransform _transform = selectedEnemy->GetActorTransform();
	FString  _name = UKismetSystemLibrary::GetDisplayName(selectedEnemy);
	FString _number = FString::FromInt(selectedEnemy->fsm-> patrolPointList.Num() + 1);
	FString _label = UKismetStringLibrary::Concat_StrStr(_name, "_Point");
	_label = UKismetStringLibrary::Concat_StrStr(_label, _number);
	auto point = gamemode->CreatePatrolPoint(_transform, _label);
	selectedEnemy->fsm->patrolPointList.Add(point);
}