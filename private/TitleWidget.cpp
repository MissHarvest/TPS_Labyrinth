// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "UISubSystem.h"

void UTitleWidget::NativeConstruct()
{
	btn_Start->OnClicked.Clear();
	btn_Setting->OnClicked.Clear();
	btn_Quit->OnClicked.Clear();

	btn_Start->OnClicked.AddDynamic(this, &UTitleWidget::ClickStartBtn);
	btn_Setting->OnClicked.AddDynamic(this, &UTitleWidget::ClickSetBtn);
	btn_Quit->OnClicked.AddDynamic(this, &UTitleWidget::ClickQuitBtn);
}

void UTitleWidget::ClickStartBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMap");
}

void UTitleWidget::ClickSetBtn()
{
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ShowUI("Setting");
}

void UTitleWidget::ClickQuitBtn()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}