// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enums.h"
#include "TPS_LabyrinthGameModeBase.generated.h"

// this struct has transform and name
USTRUCT(Atomic, BlueprintType)
struct FSaveData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
};

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API ATPS_LabyrinthGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATPS_LabyrinthGameModeBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	template <class T>
	T* SpawnActor(FTransform transform)
	{
		auto cam = GetWorld()->SpawnActor<T>(T::StaticClass, transform);
		return cam;
	}

	void SetViewTarget(AActor* target, bool showMouse);
	//void AddToViewport(); editWidget 클래스 생성.
	bool LoadGame();
	class AEditCamera* editCamera;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEditCamera> editCamFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mode)
		EEnterType entermode = EEnterType::Edit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = var)
		class AActor* selectedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = var)
		TArray<APatrolPoint*> objects;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = var)
		TArray<class AChest*> chests;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = var)
		TArray<class AEnemy*> enemys;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class APatrolPoint> patrolFactory;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AEnemy> enemyFactory;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AActor> chestFactory;

	UFUNCTION(BlueprintCallable)
		APatrolPoint* CreatePatrolPoint(FTransform transform, FString name);

	UFUNCTION(BlueprintCallable)
		bool CreateEnemy(FTransform transform);

	UFUNCTION(BlueprintCallable)
		void CreateChest(FTransform transform);

	UFUNCTION(BlueprintCallable)
		bool SaveActors();
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class USaveActorNameAndTransform> saveActorFactory;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> editWidget;
	UPROPERTY()
		class UUserWidget* editUI;
	float escapeTimer;

	UFUNCTION()
		void TogglePauseUI();

	UPROPERTY()
		class APlayerController* playerController;
};
