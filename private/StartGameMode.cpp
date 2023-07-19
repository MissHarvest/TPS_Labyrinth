// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "TitleWidget.h"
#include <Kismet/GameplayStatics.h>
#include "UISubSystem.h"

AStartGameMode::AStartGameMode()
{
	//ConstructorHelpers::FClassFinder<UTitleWidget> tempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UIs/WBP_Title.WBP_Title_C'"));
	/////Script/UMGEditor.WidgetBlueprint'/Game/UIs/WBP_Title.WBP_Title'
	//if (tempWidget.Succeeded())
	//{
	//	titleWidget = tempWidget.Class;
	//}

	ConstructorHelpers::FObjectFinder<USoundBase> _bgmSound(TEXT("SoundWave'/Game/Sounds/BGM.BGM'"));
	if (_bgmSound.Succeeded())
	{
		bgmSound = _bgmSound.Object;
	}
}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ShowUI("Title");

	//if (titleWidget == nullptr) return;
	//titleUI = CreateWidget<UTitleWidget>(GetWorld(), titleWidget);
	//titleUI->AddToViewport();

	// Audio Actor 만드는 함수가 따로 있었던거같음.
	UGameplayStatics::PlaySound2D(GetWorld(), bgmSound);
	UE_LOG(LogTemp, Warning, TEXT("AStart Game Mode BeingPlay"));
}

// /Script/UMGEditor.WidgetBlueprint'/Game/UIs/WBP_Title.WBP_Title'