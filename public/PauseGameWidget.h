// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "PauseGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UPauseGameWidget : public UWidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	virtual bool IsPopup() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Main;
	UFUNCTION()
		void ClickMainBtn();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Continue;
	UFUNCTION()
		void ClickContinueBtn();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Setting;
	UFUNCTION()
		void ClickSettingBtn();
};
