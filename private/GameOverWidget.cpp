// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UGameOverWidget::NativeConstruct()
{
	btn_Main->OnClicked.Clear();
	btn_Main->OnClicked.AddDynamic(this, &UGameOverWidget::ClickMainBtn);	
}

void UGameOverWidget::ClickMainBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TitleMap");
}