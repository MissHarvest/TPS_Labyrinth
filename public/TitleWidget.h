// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UTitleWidget : public UWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Start;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Setting;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Quit;

	UFUNCTION()
		void ClickStartBtn();
	UFUNCTION()
		void ClickSetBtn();
	UFUNCTION()
		void ClickQuitBtn();
};
