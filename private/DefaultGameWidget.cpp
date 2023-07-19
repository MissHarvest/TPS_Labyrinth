// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>
#include "BasicPlayer.h"
#include "PlayerAttackComponent.h"

void UDefaultGameWidget::NativeConstruct()
{
	auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	player = Cast<ABasicPlayer>(character);
	check(player);
	Update();
}

void UDefaultGameWidget::Update()
{
	// Bullet //
	int32 loadedCount = 0;
	int32 extraCount = 0;
	player->GetMagazine(loadedCount, extraCount);
	FString format = FString::Printf(TEXT("%2d / %2d"), loadedCount, extraCount);
	bulletText->SetText(FText::FromString(format));
	
	// HP //
	int32 hp;
	int32 maxhp;
	player->GetHP(hp, maxhp);
	float ratio = (float)hp / (float)maxhp;
	UE_LOG(LogTemp, Warning, TEXT("Rat(%f) , hp(%f), maxhp(%f)"), ratio, (float)hp, (float)maxhp);
	hpBar->SetPercent(ratio);
}