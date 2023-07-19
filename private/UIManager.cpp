// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include <Blueprint/UserWidget.h>


void UUIManager::CreateOrAddToViewport(TSubclassOf<UUserWidget> widget)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateOrAddToViewport"));
	//CreateWidget<UUserWidget>(GetWorld(), widget);
}