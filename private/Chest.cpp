// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include <Components/SphereComponent.h>
#include <Components/ArrowComponent.h>
#include "BasicPlayer.h"
#include "TPS_LabyrinthGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "UISubSystem.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(220);
	
	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMeshComp->SetupAttachment(sphereComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/Megascans/3D_Assets/Small_Wooden_Coffer_ucnhfgviw/S_Small_Wooden_Coffer_ucnhfgviw_lod3.S_Small_Wooden_Coffer_ucnhfgviw_lod3'"));
	if (tempStaticMesh.Succeeded())
	{
		staticMeshComp->SetStaticMesh(tempStaticMesh.Object);
		staticMeshComp->SetRelativeScale3D(FVector(10, 7.5f, 7.5f));
	}

	arrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	arrowComp->SetupAttachment(sphereComp);
	arrowComp->SetRelativeRotation(FRotator(0, 90, 0));
	arrowComp->SetRelativeScale3D(FVector(1.8f));
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	auto gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode)
	{
		if (gamemode->entermode == EEnterType::Normal)
		{
			//arrowComp->bHiddenInGame = true;
			arrowComp->SetHiddenInGame(true);
		}
	}

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AChest::OnChestOverlap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &AChest::OnChestEndOverlap);
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::OnChestOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ABasicPlayer>(OtherActor);	
	if (player == nullptr) return;	
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ToggleInteractionUI();
	player->getBulletDelegate.BindUFunction(this, TEXT("Interaction"));
}

void AChest::OnChestEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto player = Cast<ABasicPlayer>(OtherActor);
	if (player == nullptr) return;
	auto ui = GetGameInstance()->GetSubsystem<UUISubSystem>();
	ui->ToggleInteractionUI();
	player->getBulletDelegate.Clear();
}

void AChest::Interaction()
{
	Destroy();
}
