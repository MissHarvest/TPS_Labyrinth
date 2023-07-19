// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicPlayer.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractionDelegate);

UCLASS()
class TPS_LABYRINTH_API ABasicPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Visibleanywhere, Category = Camera)
		class USpringArmComponent* springArmComp;
	UPROPERTY(Visibleanywhere, Category = Camera)
		class UCameraComponent* camComp;
	UPROPERTY(VisibleAnywhere, Category = Component)
		class UPlayerMovementComponent* movementComp;
	UPROPERTY(VisibleAnywhere, Category = Component)
		class UPlayerAttackComponent* attackComp;
public: // 이전에 public 이었는데 private 로 바꾸면서 오류가 생겼다.
	UPROPERTY(Visibleanywhere, Category = Fire)
		class UStaticMeshComponent* targetComp;

public:	
	FInteractionDelegate getBulletDelegate;
	class UPlayerAnim* anim;
	void Interact();
	UPROPERTY()
		int32 maxHP = 5;
	UPROPERTY(VisibleAnywhere, Category = Status)
		int32 hp = 5;
	
	UFUNCTION()
		void Damaged(int32 dmg);

	UFUNCTION()
		void SendEvent();

	UFUNCTION()
		void GetMagazine(int32& loaded, int32& extra);

	UFUNCTION()
		void GetHP(int32& cur, int32& max);
};
