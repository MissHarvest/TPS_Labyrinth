// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChestEditWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UChestEditWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_TurnChest;
	UPROPERTY()
		class AChest* selectedChest;
	UFUNCTION()
		void ClickTurnChestBtn();
};
