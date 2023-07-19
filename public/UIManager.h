// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TPS_LABYRINTH_API UUIManager : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		class TSubclassOf<class UDefaultGameWidget> defaultgameWidget;
	void CreateOrAddToViewport(TSubclassOf<UUserWidget> widget);
};
