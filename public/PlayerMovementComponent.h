// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UPlayerMovementComponent : public UPlayerBaseComponent
{
	GENERATED_BODY()
public:
	UPlayerMovementComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

private:
	// �¿� ȸ�� �Է� ó��
	void Turn(float value);
	// ���� ȸ�� �Է� ó��
	void LookUp(float value);

private:
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		float walkSpeed = 200;
	FVector moveDirection;

	void SetMoveDirection_X(float value);
	void SetMoveDirection_Y(float value);

	void Move();
};
