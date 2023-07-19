// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	bool isPopup = false;
public:
	virtual bool IsPopup() { return isPopup; }
	virtual void Update() {};
};
