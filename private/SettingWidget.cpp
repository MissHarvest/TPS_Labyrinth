// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingWidget.h"
#include <Components/Slider.h>
#include "Components/Button.h"
#include "UISubSystem.h"
#include <Kismet/GameplayStatics.h>

void USettingWidget::NativeConstruct()
{
	isPopup = true;
	btn_Close->OnClicked.Clear();
	btn_Close->OnClicked.AddDynamic(this, &USettingWidget::Close);

	slider_MasterVolume->SetValue(masterVolume);
	slider_BGMVolume->SetValue(bgmVolmue);
	slider_EffectVolume->SetValue(sfxVolume);
}

bool USettingWidget::IsPopup()
{
	return isPopup;
}

void USettingWidget::Close()
{
	masterVolume = slider_MasterVolume->GetValue();
	bgmVolmue = slider_BGMVolume->GetValue();
	sfxVolume = slider_EffectVolume->GetValue();
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ClosePopup();
}