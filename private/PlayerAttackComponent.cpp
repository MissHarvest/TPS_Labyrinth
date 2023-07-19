// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAttackComponent.h"
#include "Bullet.h"
#include "PlayerAnim.h"
#include <Kismet/KismetSystemLibrary.h>
#include <UISubSystem.h>

UPlayerAttackComponent::UPlayerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	InitailizeFactories();
}

void UPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	anim = Cast<UPlayerAnim>(this->Actor->GetMesh()->GetAnimInstance());
	if (CheckFactoriesValid() == false)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit, true);
	}
}

void UPlayerAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	timer += DeltaTime;
}

void UPlayerAttackComponent::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("Fire"), this, &UPlayerAttackComponent::Fire);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &UPlayerAttackComponent::Reload);
}

void UPlayerAttackComponent::InitailizeFactories()
{
	ConstructorHelpers::FClassFinder<ABullet> BP_Bullet(TEXT("Blueprint'/Game/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (BP_Bullet.Succeeded())
	{
		bulletFactory = BP_Bullet.Class;
	}

	ConstructorHelpers::FClassFinder<AActor> BP_Flash(TEXT("Blueprint'/Game/Blueprints/BP_MuzzleFlash.BP_MuzzleFlash_C'"));
	if (BP_Flash.Succeeded())
	{
		flashFactory = BP_Flash.Class;
	}
}

bool UPlayerAttackComponent::CheckFactoriesValid()
{	
	if (IsValid(bulletFactory) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet Factory is not valid - Player Attack Component"));
		return false;
	}
	if (IsValid(flashFactory) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Flash Factory is not valid - Player Attack Component"));
		return false;
	}
	return true;	
}

void UPlayerAttackComponent::Fire(float value)
{
	if (value != 1) return;
	if (bReload) return;
	if (loadedBulletCount <= 0)
	{
		Reload();
		return;
	}
	if (timer < delay) return;
	muzzle = this->Actor->GetMesh()->GetSocketTransform(TEXT("Muzzle_02"));

	anim->PlayAttackAnim();
	
	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, muzzle);	
	bullet->SetTargetPosition(this->Actor->targetComp->GetComponentLocation());
	loadedBulletCount--;

	auto flash = GetWorld()->SpawnActor<AActor>(flashFactory, muzzle);	
	timer = 0;

	UpdateUI();
}

void UPlayerAttackComponent::Reload()
{
	if (extraBulletCount <= 0) return;
	if (loadedBulletCount >= MAX_RELOAD) return;
	bReload = true;
	anim->PlayReloadAnim();

	int32 totalBulletCount = loadedBulletCount + extraBulletCount;

	if (totalBulletCount >= MAX_RELOAD)
	{
		int32 remainingBulletCount = loadedBulletCount;
		loadedBulletCount = MAX_RELOAD;
		extraBulletCount = extraBulletCount - MAX_RELOAD + remainingBulletCount;
	}
	else
	{
		loadedBulletCount = totalBulletCount;
		extraBulletCount = 0;
	}
	
	UpdateUI();
}

void UPlayerAttackComponent::SetReload(bool value)
{
	bReload = value;
}

void UPlayerAttackComponent::GetBullet()
{
	extraBulletCount += MAX_RELOAD; 
	Reload();
}

void UPlayerAttackComponent::UpdateUI()
{
	auto ui = GetWorld()->GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->Update();
}

void UPlayerAttackComponent::GetBulletCount(int32& loaded, int32& extra)
{
	loaded = loadedBulletCount;
	extra = extraBulletCount;
}