// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UGameOverWidget : public UWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_Main;
	UFUNCTION()
		void ClickMainBtn();
};
