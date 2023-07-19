// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AStartGameMode();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UTitleWidget> titleWidget;
	UPROPERTY()
		class UTitleWidget* titleUI;

	UPROPERTY()
		class USoundBase* bgmSound;
};
