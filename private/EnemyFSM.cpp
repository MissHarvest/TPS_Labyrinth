// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "BasicPlayer.h"
#include "Enemy.h"
#include "EnemyAnim.h"
#include <Components/CapsuleComponent.h>
#include <EngineUtils.h>
#include "PatrolPoint.h"
// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	UE_LOG(LogTemp, Warning, TEXT("Harvest [UEnemyFSM] > UEnemyFSM ()"));
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Harvest [UEnemyFSM] > UEnemyFSM () > Exit"));
	// ...	

	ConstructorHelpers::FObjectFinder<USoundBase> _baseSound(TEXT("SoundWave'/Game/Sounds/Monster.Monster'"));
	if (_baseSound.Succeeded())
	{
		baseSound = _baseSound.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundAttenuation> _attention(TEXT("SoundAttenuation'/Game/Sounds/SA_Enemy.SA_Enemy'"));
	if (_attention.Succeeded())
	{
		soundAttention = _attention.Object;
	}
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Harvest [UEnemyFSM] > BeginPlay ()"));
	// ...	
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABasicPlayer::StaticClass());
	me = Cast<AEnemy>(GetOwner());
	player = Cast<ABasicPlayer>(actor);
	if (player == nullptr) return;

	nextIndex = 1;

	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());
}

// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damaged:
		DamagedState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}

void UEnemyFSM::ChangeState(EEnemyState state)
{
	mState = state;
	anim->animState = mState;
}

void UEnemyFSM::IdleState()
{
	timer += GetWorld()->DeltaTimeSeconds;
	if (timer >= waitingTime)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), baseSound, me->GetActorLocation(), 1, 1, 0, soundAttention);
		SetNextDestination();
		ChangeState(EEnemyState::Move);
		timer = 0;
	}
}

void UEnemyFSM::SetNextDestination()
{
	if (destination == nextPoint)
	{
		nextPoint = cyclicArray[nextIndex]->GetActorLocation();
		nextIndex++;
		if (nextIndex >= cyclicArray.Num())
			nextIndex = 0;
	}
	destination = nextPoint;
}

void UEnemyFSM::MoveState()
{
	direction = destination - me->GetActorLocation();
	direction.Z = 0;
	me->AddMovementInput(direction.GetSafeNormal());
	
	if (FindTarget() == false)
	{
		float distToDestination = FVector::Dist2D(destination, me->GetActorLocation());
		if (distToDestination <= 10.0f)
		{
			ChangeState(EEnemyState::Idle);
		}
		return;
	}

	if (TargetWithInAttackRange() == false)
	{
		destination = player->GetActorLocation();
		return;
	}
	
	ChangeState(EEnemyState::Attack);
	timer = attackDelay;
}

bool UEnemyFSM::FindTarget()
{
	float distToPlayer = FVector::Dist2D(player->GetActorLocation(), me->GetActorLocation());
	if (distToPlayer > detectDist) return false;
	if (CheckTargetWithInViewAngle() == false) return false;
	if (CheckWall()) return false;
	return true;
}

void UEnemyFSM::AttackState()
{
	if (anim->bAttackPlay == true) return;
	timer += GetWorld()->DeltaTimeSeconds;
	
	if (timer >= attackDelay)
	{
		me->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(direction, me->GetActorUpVector()));
		anim->bAttackPlay = true;
		timer = 0;
	}
		

	if (FindTarget() == false)
	{
		ChangeState(EEnemyState::Idle);
		return;
	}

	if (TargetWithInAttackRange() == false)
	{
		ChangeState(EEnemyState::Move);		
		return;
	}
}

bool UEnemyFSM::CheckTargetWithInViewAngle()
{
	FVector forward = me->GetActorForwardVector();
	FVector target = player->GetActorLocation() - me->GetActorLocation();
	float dot = FVector::DotProduct(forward, target);
	dot /= (forward.Length()) * (target.Length());
	float rad = FMath::DegreesToRadians(detectAngle);
	bool bExist = dot < FMath::Cos(rad) ? false : true;
	return bExist;
}

bool UEnemyFSM::CheckWall()
{
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(me);
	bool bExist;
	bExist = GetWorld()->LineTraceSingleByObjectType(hitInfo, me->GetActorLocation(), player->GetActorLocation(), ECC_GameTraceChannel3);
	return bExist;
}

bool UEnemyFSM::TargetWithInAttackRange()
{
	float dist = FVector::Dist2D(player->GetActorLocation(), me->GetActorLocation());
	if (dist > reach) return false;
	return true;
}

void UEnemyFSM::Attack()
{
	if (TargetWithInAttackRange())
	{
		player->Damaged(2);
	}
}

void UEnemyFSM::DamagedState()
{	
	if (anim->bDamagedAnimPlay == false)
	{
		ChangeState(EEnemyState::Move);
		destination = player->GetActorLocation();
	}
}

void UEnemyFSM::DieState()
{
	if (anim->die == false) return;
	me->SetActorLocation(me->GetActorLocation() + FVector::DownVector * 50 * GetWorld()->DeltaTimeSeconds);
	if (me->GetActorLocation().Z < -200.0f)
	{
		me->Destroy();
	}
}

void UEnemyFSM::OnDamaged()
{
	me->hp--;
	if (me->hp > 0)
	{
		int number = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damaged%d"), number);
		anim->PlayDamagedAnim(FName(*sectionName));
		mState = EEnemyState::Damaged;
		timer = 0;
	}
	else
	{
		mState = EEnemyState::Die;
		anim->PlayDamagedAnim(TEXT("Die"));
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UEnemyFSM::FindPatrolPoint()
{
	FString name = me->name;
	UE_LOG(LogTemp, Warning, TEXT("==%s=="), *name);
	name += "_Point";	
	UE_LOG(LogTemp, Warning, TEXT("Add Patrol Point"));
	for (TActorIterator<APatrolPoint> It(GetWorld()); It; ++It)
	{
		APatrolPoint* point = *It;
		if(point->name.Contains(name))
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s]"), *point->name);
			patrolPointList.Add(point);
		}
	}

	if (patrolPointList.Num() <= 0)
	{
		PrimaryComponentTick.bCanEverTick = false;
		return;
	}

	CreateCyclicArray();
}

void UEnemyFSM::CreateCyclicArray()
{
	for (int i = 0; i < patrolPointList.Num(); i++)
	{
		cyclicArray.Add(patrolPointList[i]);
	}
	for (int i = patrolPointList.Num() - 2; i > 0; i--)
	{
		cyclicArray.Add(patrolPointList[i]);
	}
}