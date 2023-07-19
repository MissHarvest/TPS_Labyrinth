// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClearWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "TPS_LabyrinthGameModeBase.h"
#include <Components/TextBlock.h>

void UGameClearWidget::NativeConstruct()
{
	isPopup = true;
	btn_Main->OnClicked.Clear();
	btn_Main->OnClicked.AddDynamic(this, &UGameClearWidget::ClickMainBtn);

	CalculateClearTime();
}

void UGameClearWidget::ClickMainBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TitleMap");
}

void UGameClearWidget::CalculateClearTime()
{
	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	float timer = gamemode->escapeTimer;
	int32 hour = timer / 3600;
	timer -= hour * 3600;
	int32 min = timer / 60;
	timer -= 60 * min;
	int32 sec = (int32)timer;
	FString timeFormat = FString::Printf(TEXT("%2d:%2d:%2d"), hour, min, sec);
	FText text = FText::FromString(timeFormat);
	playerTimeText->SetText(text);
}

bool UGameClearWidget::IsPopup()
{
	return isPopup;
}