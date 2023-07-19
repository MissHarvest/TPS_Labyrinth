// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TPS_LABYRINTH_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(Visibleanywhere, Category = Component)
		class UBoxComponent* boxComp;
	UPROPERTY(Visibleanywhere, Category = Component)
		class UStaticMeshComponent* staticMeshComp;

	FVector direction;
	
	UPROPERTY(EditDefaultsOnly, Category = Move)
		float speed = 600.0f;
	bool bFired = false;
public:
	UFUNCTION()
		void Death();

	UFUNCTION()
		void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void SetTargetPosition(const FVector destination);

};
