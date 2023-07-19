// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UGameClearWidget : public UWidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	virtual bool IsPopup() override;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* playerTimeText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Main;
	UFUNCTION()
		void ClickMainBtn();

	void CalculateClearTime();
};


/*
UPROPERTY(EditAnywhere, meta = (BindWidget))
class UTextBlock* playerBestTimeText;
*/