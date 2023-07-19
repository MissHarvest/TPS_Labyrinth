// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPoint.h"
#include "TPS_LabyrinthGameModeBase.h"
#include <Kismet/GameplayStatics.h>
// Sets default values
APatrolPoint::APatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void APatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode == nullptr) return;
	if (EEnterType::Edit == gamemode->entermode)
	{
		SetActorHiddenInGame(false);
	}
}

// Called every frame
void APatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

