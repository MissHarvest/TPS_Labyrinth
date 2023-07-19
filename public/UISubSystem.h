// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubSystem.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UUISubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UUISubSystem();

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	TMap<FString, class UWidgetBase*> UI;
	TArray<class UWidgetBase*> popupStack;

	UPROPERTY()
		TSubclassOf<class UPauseGameWidget> PauseGameWidget;
	UPROPERTY()
		class UPauseGameWidget* PauseGameUI;
	UPROPERTY()
		TSubclassOf<class UTitleWidget> TitleWidget;
	UPROPERTY()
		class UTitleWidget* TitleUI;
	UPROPERTY()
		TSubclassOf<class UGameClearWidget> GameClearWidget;
	UPROPERTY()
		class UGameClearWidget* GameClearUI;
	UPROPERTY()
		TSubclassOf<class USettingWidget> SettingWidget;
	UPROPERTY()
		class USettingWidget* SettingUI;
	UPROPERTY()
		TSubclassOf<class UDefaultGameWidget> DefaultGameWidget;
	UPROPERTY()
		class UDefaultGameWidget* DefaultGameUI;
	UPROPERTY()
		TSubclassOf<class UUserWidget> InteractionWidget;
	UPROPERTY()
		class UUserWidget* InteractionUI;
	UPROPERTY()
		TSubclassOf<class UGameOverWidget> GameOverWidget;
	UPROPERTY()
		class UGameOverWidget* GameOverUI;

	bool bToggleUI = false;
public:
	// need widget name. ex) UTitleWidget -> Title
	void ShowUI(FString name);
	// Close recently opened Popup UI 
	void ClosePopup();
	// Call Update Function if UI have Update Function
	void Update();
	
	void ToggleInteractionUI();
};
