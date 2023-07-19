// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include "BasicPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "TPS_LabyrinthGameModeBase.h"
#include "GameClearWidget.h"
#include <Components/TextBlock.h>
#include "UISubSystem.h"

//#include <Kisme>
// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(boxComp);
	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
	{
		staticMeshComp->SetStaticMesh(tempMesh.Object);
	}
	staticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	staticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Overlap);
	staticMeshComp->SetupAttachment(boxComp);

	ConstructorHelpers::FClassFinder<UGameClearWidget> _gameClearWidget(TEXT("WidgetBlueprint'/Game/UIs/WBP_GameClear.WBP_GameClear_C'"));
	if (_gameClearWidget.Succeeded())
	{
		gameClearWidget = _gameClearWidget.Class;
	}
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnActorOverlap);
	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode == nullptr) return;
	if (EEnterType::Edit == gamemode->entermode)
	{
		SetActorHiddenInGame(false);
	}
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UGameplayStatics::level
}

void AFinishLine::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ABasicPlayer>(OtherActor);
	if (player == nullptr) return;
	
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ShowUI("GameClear");
}
