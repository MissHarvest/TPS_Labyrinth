// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayer.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "TPS_LabyrinthGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerAnim.h"
#include "Enums.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "UISubSystem.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("ABasicPlayer()"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Ä¸½¶ ÄÝ¶óÀÌ´õ H : 90, R : 65
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Meshes/Murdock.Murdock'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	// Mesh Transform . Z : -90
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Componenet"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 40, 90));
	springArmComp->bUsePawnControlRotation = true;

	camComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	camComp->SetupAttachment(springArmComp);
	camComp->SetRelativeLocation(FVector::ZeroVector);

	targetComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Component"));
	targetComp->SetupAttachment(springArmComp);
	targetComp->SetRelativeLocation(FVector(1500, 0, 0));
	targetComp->SetRelativeScale3D(FVector(0.5f));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTargetMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (tempTargetMesh.Succeeded())
	{
		targetComp->SetStaticMesh(tempTargetMesh.Object);
	}
	targetComp->SetCollisionProfileName(TEXT("NoCollision"));	
	
	// ¸®ÆÑÅä¸µ
	movementComp = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement"));
	attackComp = CreateDefaultSubobject<UPlayerAttackComponent>(TEXT("Fire"));
}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ABasicPlayer::BeginPlay()"));

	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode == nullptr) return;
	if (EEnterType::Edit == gamemode->entermode)
	{
		auto _controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		DisableInput(_controller);
	}
	else
	{
		anim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	}
}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Interaction //
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ABasicPlayer::Interact);

	movementComp->SetupInputBinding(PlayerInputComponent);
	attackComp->SetupInputBinding(PlayerInputComponent);
}

void ABasicPlayer::SendEvent()
{
	attackComp->SetReload(false);
}

void ABasicPlayer::Interact()
{
	if (getBulletDelegate.IsBound())
	{
		attackComp->GetBullet();
		getBulletDelegate.ExecuteIfBound();
	}
}

void ABasicPlayer::Damaged(int32 dmg)
{
	UE_LOG(LogTemp, Warning, TEXT("Player is damaged"));
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	hp -= dmg;
	if (hp < 0)
	{
		hp = 0;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		ui->ShowUI("GameOver");
	}
	else
	{
		ui->Update();
	}
}

void ABasicPlayer::GetMagazine(int32& loaded, int32& extra)
{
	attackComp->GetBulletCount(loaded, extra);
}

void ABasicPlayer::GetHP(int32& cur, int32& max)
{
	cur = hp;
	max = this->maxHP;
}