// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damaged,
	Die,
};

UCLASS()
class TPS_LABYRINTH_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class AEnemy* me;
	UPROPERTY()
		class ABasicPlayer* player;
	UPROPERTY()
		class UEnemyAnim* anim;
	UPROPERTY()
		class USoundBase* baseSound;
	UPROPERTY()
		class USoundAttenuation* soundAttention;

	UPROPERTY(VisibleAnywhere, Category = FSM)
		EEnemyState mState = EEnemyState::Idle;	
	float timer;

	void IdleState();
	UPROPERTY(EditDefaultsOnly, Category = FSM)
		float waitingTime = 2.0f;

	void MoveState();
	UPROPERTY(VisibleAnywhere, Category = FSM)
		TArray<class APatrolPoint*> cyclicArray;
	UPROPERTY(VisibleAnywhere, Category = FSM)
		FVector destination;
	UPROPERTY(VisibleAnywhere, Category = FSM)
		FVector nextPoint;
	float detectDist = 1500.0f;
	float detectAngle = 30.0f;
	FVector direction;	
	int32 nextIndex = 1;

	void AttackState();
	UPROPERTY(EditAnywhere, Category = FSM)
		float reach = 200.0f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackDelay = 2.0f;

	void DamagedState();

	void DieState();

	void ChangeState(EEnemyState state);

private:
	void SetNextDestination();
	// Check if there is a wall between self and player
	bool CheckWall();
	// Check if there is a wall between self and player
	bool CheckTargetWithInViewAngle();
	// Check find a target
	bool FindTarget();
	//Check if the target is within attack range
	bool TargetWithInAttackRange();
	// Make Patrol Array sorted by index
	void CreateCyclicArray(); 

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void FindPatrolPoint();	
	
	UPROPERTY(EditAnywhere, Category = FSM)
		TArray<class APatrolPoint*> patrolPointList;

	void OnDamaged();
	void Attack();
};
