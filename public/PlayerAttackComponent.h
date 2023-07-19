// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerAttackComponent.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LABYRINTH_API UPlayerAttackComponent : public UPlayerBaseComponent
{
	GENERATED_BODY()
public:
	UPlayerAttackComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Factory)
		TSubclassOf<class ABullet> bulletFactory;
	UPROPERTY(EditDefaultsOnly, Category = Factory)
		TSubclassOf<class AActor> flashFactory;
	
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		bool bReload = false;
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		class UPlayerAnim* anim;
	
	UPROPERTY(EditDefaultsOnly, Category = Bullet)
		int32 loadedBulletCount;
	UPROPERTY(EditDefaultsOnly, Category = Bullet)
		int32 extraBulletCount;
	const int32 MAX_RELOAD = 30;

	FTransform muzzle;
	float delay = 0.15f;
	float timer = 0;
	
	void Fire(float value);
	void Reload();

	void InitailizeFactories();
	bool CheckFactoriesValid();
	void UpdateUI();
public:	
	void SetReload(bool value);
	void GetBullet();
	void GetBulletCount(int32& loaded, int32& extra);
};
