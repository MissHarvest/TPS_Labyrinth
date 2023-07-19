// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyEditWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UEnemyEditWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btn_CreatePoint;
	UFUNCTION()
		void ClickCreatePointBtn();
	UPROPERTY()
		class AEnemy* selectedEnemy;
};
