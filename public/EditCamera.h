// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "EditCamera.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API AEditCamera : public ACameraActor
{
	GENERATED_BODY()
public:
	AEditCamera();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		class ATPS_LabyrinthGameModeBase* gamemode;

	void Zoom(float value);
	void MoveCamera(float value);
	FVector InitPosition = FVector::ZeroVector;
	UPROPERTY()
		class APlayerController* controller;
	void SelectActor();
	void PutActor();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UEnemyEditWidget> enemyEditWidget;
	UPROPERTY()
		class UEnemyEditWidget* enemyEditUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UChestEditWidget> chestEditWidget;
	UPROPERTY()
		class UChestEditWidget* chestEditUI;
};
