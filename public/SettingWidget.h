// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "SettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API USettingWidget : public UWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	virtual bool IsPopup() override;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class USlider* slider_MasterVolume;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class USlider* slider_EffectVolume;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class USlider* slider_BGMVolume;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Close;
	UFUNCTION()
		void Close();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float masterVolume = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float bgmVolmue = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float sfxVolume = 1;
};
