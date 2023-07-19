// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"
//#include "Enums.h"

UCLASS()
class TPS_LABYRINTH_API AEnemy : public ACharacter
{
	GENERATED_BODY()
private:
	//EActorType actorType = EActorType::Enemy;

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FString name = "";
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int hp = 3;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite, Category = FSM )
		class UEnemyFSM* fsm;

	void Damaged();
	void Attack();
};
