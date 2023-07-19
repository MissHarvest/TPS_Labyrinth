// Fill out your copyright notice in the Description page of Project Settings.


#include "UISubSystem.h"
#include <Blueprint/UserWidget.h>
#include "PauseGameWidget.h"
#include "GameClearWidget.h"
#include "SettingWidget.h"
#include "TitleWidget.h"
#include "DefaultGameWidget.h"
#include "GameOverWidget.h"

UUISubSystem::UUISubSystem()
{
	UE_LOG(LogTemp, Warning, TEXT("UI Subsystem ()"));

	ConstructorHelpers::FClassFinder<UPauseGameWidget> WBP_PauseGame(TEXT("WidgetBlueprint'/Game/UIs/WBP_PauseGame.WBP_PauseGame_C'"));
	if (WBP_PauseGame.Succeeded())
	{
		PauseGameWidget = WBP_PauseGame.Class;
	}

	ConstructorHelpers::FClassFinder<UTitleWidget> WBP_Title(TEXT("WidgetBlueprint'/Game/UIs/WBP_Title.WBP_Title_C'"));
	if (WBP_Title.Succeeded())
	{
		TitleWidget = WBP_Title.Class;
	}

	ConstructorHelpers::FClassFinder<USettingWidget> WBP_Setting(TEXT("WidgetBlueprint'/Game/UIs/WBP_Setting.WBP_Setting_C'"));
	if (WBP_Setting.Succeeded())
	{
		SettingWidget = WBP_Setting.Class;
	}

	ConstructorHelpers::FClassFinder<UGameClearWidget> WBP_GameClear(TEXT("WidgetBlueprint'/Game/UIs/WBP_GameClear.WBP_GameClear_C'"));
	if (WBP_GameClear.Succeeded())
	{
		GameClearWidget = WBP_GameClear.Class;
	}
	
	ConstructorHelpers::FClassFinder<UDefaultGameWidget> WBP_DefaultGame(TEXT("WidgetBlueprint'/Game/UIs/WBP_DefaultGame.WBP_DefaultGame_C'"));
	if (WBP_DefaultGame.Succeeded())
	{
		DefaultGameWidget = WBP_DefaultGame.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> WBP_Interaction(TEXT("WidgetBlueprint'/Game/UIs/WBP_Interaction.WBP_Interaction_C'"));
	if (WBP_Interaction.Succeeded())
	{
		InteractionWidget = WBP_Interaction.Class;
	}

	ConstructorHelpers::FClassFinder<UGameOverWidget> WBP_GameOver(TEXT("WidgetBlueprint'/Game/UIs/WBP_GameOver.WBP_GameOver_C'"));
	if (WBP_GameOver.Succeeded())
	{
		GameOverWidget = WBP_GameOver.Class;
	}
}

void UUISubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	if (TitleWidget)
	{
		TitleUI = CreateWidget<UTitleWidget>(GetWorld(), TitleWidget);
		UI.Add("Title", TitleUI);
	}

	if (DefaultGameWidget)
	{
		DefaultGameUI = CreateWidget<UDefaultGameWidget>(GetWorld(), DefaultGameWidget);
		UI.Add("DefaultGame", DefaultGameUI);
	}

	if (GameClearWidget)
	{
		GameClearUI = CreateWidget<UGameClearWidget>(GetWorld(), GameClearWidget);
		UI.Add("GameClear", GameClearUI);
	}

	if (PauseGameWidget)
	{
		PauseGameUI = PauseGameUI = CreateWidget<UPauseGameWidget>(GetWorld(), PauseGameWidget);
		UI.Add("PauseGame", PauseGameUI);
	}

	if (SettingWidget)
	{
		SettingUI = CreateWidget<USettingWidget>(GetWorld(), SettingWidget);
		UI.Add("Setting", SettingUI);
	}

	if (GameOverWidget)
	{
		GameOverUI = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidget);
		UI.Add("GameOver", GameOverUI);
	}

	if (InteractionWidget)
	{
		InteractionUI = CreateWidget<UUserWidget>(GetWorld(), InteractionWidget);
	}
}

void UUISubSystem::ShowUI(FString name)
{
	if (UI.Contains(*name))
	{
		UI[*name]->AddToViewport();
		
		if (UI[*name]->IsPopup())
		{
			popupStack.Push(UI[*name]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Dont Exist [%s]"),*name);
	}
}

void UUISubSystem::ClosePopup()
{
	if (popupStack.Num() <= 0) return;
	auto popup = popupStack.Pop();
	popup->RemoveFromParent();
}

void UUISubSystem::Update()
{
	for (auto iter = UI.CreateConstIterator(); iter; ++iter)
	{
		iter.Value()->Update();
	}
}

void UUISubSystem::ToggleInteractionUI()
{
	if (bToggleUI)
	{
		InteractionUI->RemoveFromParent(); 
		bToggleUI = false;
	}
	else
	{
		InteractionUI->AddToViewport();
		bToggleUI = true;
	}
}