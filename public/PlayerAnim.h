// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnim();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MoveAnim)
		float speedX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MoveAnim)
		float speedY;

	UPROPERTY(EditDefaultsOnly, Category = FireMontage)
		class UAnimMontage* attackMontage;	
	UPROPERTY(EditDefaultsOnly, Category = FireMontage)
		class UAnimMontage* reloadMontage;

	UFUNCTION(BlueprintCallable, Category = FSMEvent)
		void PlayAttackAnim();

	UFUNCTION(BlueprintCallable, Category = FSMEvent)
		void PlayReloadAnim();

	UFUNCTION(BlueprintCallable, Category = Event)
		void ReloadEndEvent();

	UPROPERTY(EditDefaultsOnly, Category = Sound)
		class USoundBase* fireSound;

	UPROPERTY()
		class ABasicPlayer* Actor;
};
