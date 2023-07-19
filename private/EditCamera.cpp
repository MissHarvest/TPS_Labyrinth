// Fill out your copyright notice in the Description page of Project Settings.


#include "EditCamera.h"
#include "Enums.h"
#include "TPS_LabyrinthGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>
#include "EnemyEditWidget.h"
#include "ChestEditWidget.h"
#include "Enemy.h"
#include "Chest.h"
AEditCamera::AEditCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	auto cam = GetCameraComponent();
	cam->ProjectionMode = ECameraProjectionMode::Orthographic;
	cam->OrthoWidth = 3000;
	
	// /Script/UMGEditor.WidgetBlueprint'/Game/UIs/WBP_EnemyEdit.WBP_EnemyEdit'
	ConstructorHelpers::FClassFinder<UEnemyEditWidget> tempWidget(TEXT("WidgetBlueprint'/Game/UIs/WBP_EnemyEdit.WBP_EnemyEdit_C'"));
	if (tempWidget.Succeeded())
	{
		enemyEditWidget = tempWidget.Class;
	}
	//autoactiveplayer

}

void AEditCamera::BeginPlay()
{
	Super::BeginPlay();
	gamemode = Cast<ATPS_LabyrinthGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode == nullptr) return;
	if (EEnterType::Edit == gamemode->entermode)
	{
		controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		EnableInput(controller);
	}
	enemyEditUI = CreateWidget<UEnemyEditWidget>(GetWorld(), enemyEditWidget);
	if (enemyEditUI == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("enemy edit ui is nullptr"));
	chestEditUI = CreateWidget<UChestEditWidget>(GetWorld(), chestEditWidget);
	if (InputComponent)
	{
		InputComponent->BindAxis("Zoom", this, &AEditCamera::Zoom);
		InputComponent->BindAxis("Drag", this, &AEditCamera::MoveCamera);

		InputComponent->BindAction("Release", IE_Pressed, this, &AEditCamera::SelectActor);
		InputComponent->BindAction("Release", IE_Released, this, &AEditCamera::PutActor);
	}
}

void AEditCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (gamemode->selectedActor == nullptr) return;
	FVector mousePosition3D;
	FVector mouseDirection3D;
	controller->DeprojectMousePositionToWorld(mousePosition3D, mouseDirection3D);
	auto actor = gamemode->selectedActor;
	float actorOriginZLocation = actor->GetActorLocation().Z;
	FVector setLocation = FVector(mousePosition3D.X, mousePosition3D.Y, actorOriginZLocation);
	actor->SetActorLocation(setLocation);
}

void AEditCamera::Zoom(float value)
{
	auto camera = GetCameraComponent();
	float setupWidth = camera->OrthoWidth + value * 500;
	if (setupWidth < 3000) setupWidth = 3000;
	else if (setupWidth > 10000) setupWidth = 10000;
	camera->OrthoWidth = setupWidth;
}

void AEditCamera::MoveCamera(float value)
{
	if (1.0f != value)
	{
		InitPosition = FVector::ZeroVector;
		return;
	}

	if (FVector::ZeroVector == InitPosition)
	{
		controller->GetMousePosition(InitPosition.Y, InitPosition.X);
	}

	FVector dragPosition;
	controller->GetMousePosition(dragPosition.Y, dragPosition.X);
	FVector moveDirection = dragPosition - InitPosition;
	moveDirection.Y *= -1;
	FVector movePosition = GetActorLocation() + moveDirection;
	SetActorLocation(movePosition, true);
}

void AEditCamera::SelectActor()
{
	//FVector mousePosition;
	//FVector mouseDirection;
	//controller->DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	FVector2D mousePosition2D;
	controller->GetMousePosition(mousePosition2D.X, mousePosition2D.Y);
	FHitResult hitresult;
	FCollisionQueryParams params;	
	TArray<TEnumAsByte<EObjectTypeQuery>> temp;
	temp.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	temp.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel5));
	temp.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel6));
		
	controller->GetHitResultAtScreenPosition(mousePosition2D, temp, false, hitresult);	
	auto enemy = Cast<AEnemy>(hitresult.GetActor());
	if (enemy)
	{
		gamemode->selectedActor = hitresult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Selected Actor is Enemy"));
		enemyEditUI->selectedEnemy = enemy;
		enemyEditUI->AddToViewport();		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast Enemy"));
		enemyEditUI->RemoveFromParent();
	}

	auto chest = Cast<AChest>(hitresult.GetActor());
	if (chest)
	{
		gamemode->selectedActor = hitresult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Selected Actor is Chest"));
		chestEditUI->selectedChest = chest;
		chestEditUI->AddToViewport();
	}
	else
	{
		chestEditUI->RemoveFromParent();
	}
}

void AEditCamera::PutActor()
{
	gamemode->selectedActor = nullptr;
}