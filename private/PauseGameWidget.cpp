// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseGameWidget.h"
#include <Components/Button.h>
#include "SettingWidget.h"
#include <Kismet/GameplayStatics.h>
#include "UISubSystem.h"

void UPauseGameWidget::NativeConstruct()
{
	isPopup = true;
	btn_Main->OnClicked.Clear();
	btn_Continue->OnClicked.Clear();
	btn_Setting->OnClicked.Clear();
	btn_Main->OnClicked.AddDynamic(this, &UPauseGameWidget::ClickMainBtn);
	btn_Continue->OnClicked.AddDynamic(this, &UPauseGameWidget::ClickContinueBtn);
	btn_Setting->OnClicked.AddDynamic(this, &UPauseGameWidget::ClickSettingBtn);
}

void UPauseGameWidget::ClickSettingBtn()
{
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ShowUI("Setting");
}

void UPauseGameWidget::ClickMainBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TitleMap");
}

void UPauseGameWidget::ClickContinueBtn()
{
	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playerController->SetShowMouseCursor(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ClosePopup();
}

bool UPauseGameWidget::IsPopup()
{
	return isPopup;
}