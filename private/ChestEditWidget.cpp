// Fill out your copyright notice in the Description page of Project Settings.


#include "ChestEditWidget.h"
#include <Components/Button.h>
#include "Chest.h"
void UChestEditWidget::NativeConstruct()
{
	btn_TurnChest->OnClicked.Clear();
	btn_TurnChest->OnClicked.AddDynamic(this, &UChestEditWidget::ClickTurnChestBtn);
}

void UChestEditWidget::ClickTurnChestBtn()
{
	if (selectedChest == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Chest not found"));
		return;
	}

	auto initRotation = selectedChest->GetActorRotation().Yaw;
	initRotation += 90;
	selectedChest->SetActorRotation(FRotator(0, initRotation, 0));
}

