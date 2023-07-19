// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "TPS_LabyrinthGameModeBase.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include "Enums.h"
#include "EnemyAnim.h"
//#include "Manager.h"
// Sets default values
AEnemy::AEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Harvest [AEnemy] > AEnemy ()"));
	PrimaryActorTick.bCanEverTick = true;
	// Set Skeletal Mesh //
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Model/vampire_a_lusth.vampire_a_lusth'"));
	if (tempSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempSkeletalMesh.Object);
	}
	// Set Mesh's Location and Rotation //
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	
	ConstructorHelpers::FClassFinder<UAnimInstance> tempAnimClass(TEXT("AnimBlueprint'/Game/Animation/ABP_Enemy.ABP_Enemy_C'"));
	///Script/Engine.AnimBlueprint'/Game/Animation/ABP_Enemy.ABP_Enemy'
	if (tempAnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnimClass.Class);
		UE_LOG(LogTemp, Warning, TEXT("animClass Succeed"));
	}

	// Add fsm Component //
	UE_LOG(LogTemp, Warning, TEXT("Harvest [AEnemy] > AEnemy () > Create FSM ()"));
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
	//GetCharacterMovement()
	GetCharacterMovement()->bOrientRotationToMovement = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UE_LOG(LogTemp, Warning, TEXT("Visaul Studio Test Code"));
	UE_LOG(LogTemp, Warning, TEXT("Harvest [AEnemy] > AEnemy () > Exit"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Harvest [AEnemy] > BeginPlay ()"));
	Super::BeginPlay();
	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode->entermode == EEnterType::Edit)
	{
		fsm->SetComponentTickEnabled(false);
	}
	//AManager::Test<class UDefaultGameWidget>();
	UE_LOG(LogTemp, Warning, TEXT("Harvest [AEnemy] > BeginPlay ()> Exit"));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::Damaged()
{
	fsm->OnDamaged();
}

void AEnemy::Attack()
{
	fsm->Attack();
}
