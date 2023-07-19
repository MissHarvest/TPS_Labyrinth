// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnim.h"
#include "BasicPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

UPlayerAnim::UPlayerAnim()
{
	UE_LOG(LogTemp, Warning, TEXT("UPlayerAnim()"));
	ConstructorHelpers::FObjectFinder<USoundBase> FIRE_SOUND(TEXT("SoundWave'/Game/Sounds/Shot.Shot'"));
	if (FIRE_SOUND.Succeeded())
	{
		fireSound = FIRE_SOUND.Object;
	}
}

void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	UE_LOG(LogTemp, Warning, TEXT("NativeInitializeAnimation()"));
	Actor = Cast<ABasicPlayer>(TryGetPawnOwner());
	if (Actor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Anim Owner is not BasicPlayer - PlayerAnim"));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("NativeUpdateAnimation()"));
	if (Actor == nullptr) return;
	FVector velocity = this->Actor->GetVelocity();
	FVector forward = this->Actor->GetActorForwardVector();
	speedX = FVector::DotProduct(forward, velocity);

	FVector right = this->Actor->GetActorRightVector();
	speedY = FVector::DotProduct(right, velocity);
}

void UPlayerAnim::PlayAttackAnim()
{
	Montage_Play(attackMontage);
	if (IsValid(fireSound))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), fireSound, 1, 1, 0.2f);
	}
}

void UPlayerAnim::PlayReloadAnim()
{
	Montage_Play(reloadMontage);
}

void UPlayerAnim::ReloadEndEvent()
{
	auto player = Cast<ABasicPlayer>(TryGetPawnOwner());
	player->SendEvent();
}