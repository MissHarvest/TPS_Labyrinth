// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "DefaultGameWidget.generated.h"
//#include <Components/ProgressBar.h>
/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UDefaultGameWidget : public UWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	class ABasicPlayer* player;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* bulletText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* hpBar;
public:
	virtual void Update() override;
};
