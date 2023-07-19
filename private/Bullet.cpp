// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Enemy.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(12, 4, 4));

	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	staticMeshComp->SetupAttachment(boxComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	if (tempMesh.Succeeded())
	{
		staticMeshComp->SetStaticMesh(tempMesh.Object);
	}
	staticMeshComp->SetRelativeLocationAndRotation(FVector(0, 0, -3), FRotator(0, -90, 0));
	staticMeshComp->SetRelativeScale3D(FVector(0.2f));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle destroyTimer;
	GetWorld()->GetTimerManager().SetTimer(destroyTimer, this, &ABullet::Death, 2.0f, false);
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bFired) return;
	SetActorLocation(GetActorLocation() + direction * speed * DeltaTime);
}

void ABullet::Death()
{
	Destroy();
}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBulletOverlap"));
	auto enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		enemy->Damaged();
	}
	Destroy();
}

void ABullet::SetTargetPosition(const FVector destination)
{
	direction = destination - GetActorLocation();
	direction.Normalize();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
	bFired = true;
}
