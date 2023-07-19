// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "EnemyFSM.h"
#include "Enemy.h"
#include <Animation/AnimMontage.h>

UEnemyAnim::UEnemyAnim()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> _damagedMontage(TEXT("AnimMontage'/Game/Animation/AM_EnemyDamaged.AM_EnemyDamaged'"));
	if (_damagedMontage.Succeeded())
	{
		animMontage = _damagedMontage.Object;
	}
}

void UEnemyAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	me = Cast<AEnemy>(TryGetPawnOwner());
	fsm = me->fsm;
	UE_LOG(LogTemp, Warning, TEXT("Enemy Anim - Native Begin Player : Set FSM"));
}

void UEnemyAnim::PlayDamagedAnim(FName sectionName)
{
	me->PlayAnimMontage(animMontage, 1.0f, sectionName);
	bDamagedAnimPlay = true;
}

void UEnemyAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
	UE_LOG(LogTemp, Warning, TEXT("EnemyAnim > OnEndAttackAnimation"));
}

void UEnemyAnim::EndDamagedAnim() 
{
	bDamagedAnimPlay = false;
}

void UEnemyAnim::AttackAnim()
{
	me->Attack();
}