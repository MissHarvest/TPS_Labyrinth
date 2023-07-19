// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UEnemyAnim();
public:
	void NativeBeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
		EEnemyState animState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
		bool bAttackPlay;
	bool bDamagedAnimPlay = false;
	UFUNCTION(BlueprintCallable, Category = FSMEvent)
		void OnEndAttackAnimation();
	class UEnemyFSM* fsm;

	UPROPERTY()
		class AEnemy* me;

	UPROPERTY()
		class UAnimMontage* animMontage;

	UFUNCTION(BlueprintCallable, Category = FSMEvent)
		void PlayDamagedAnim(FName sectionName);

	UFUNCTION(BlueprintCallable, Category = FSMEvent)
		void EndDamagedAnim();

	UFUNCTION(BlueprintCallable, Category = FSMEvent)
		void AttackAnim();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSMEvent)
		bool die;
};
