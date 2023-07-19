// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// this->Actor->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move();
}

void UPlayerMovementComponent::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &UPlayerMovementComponent::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &UPlayerMovementComponent::LookUp);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &UPlayerMovementComponent::SetMoveDirection_Y);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &UPlayerMovementComponent::SetMoveDirection_X);
}

void UPlayerMovementComponent::Turn(float value)
{
	this->Actor->AddControllerYawInput(value);
}

void UPlayerMovementComponent::LookUp(float value)
{
	this->Actor->AddControllerPitchInput(value);
}

void UPlayerMovementComponent::SetMoveDirection_X(float value)
{
	moveDirection.X = value;
}

void UPlayerMovementComponent::SetMoveDirection_Y(float value)
{
	moveDirection.Y = value;
}

void UPlayerMovementComponent::Move()
{
	FRotator rotate = this->Actor->GetControlRotation();
	rotate.Pitch = 0;
	moveDirection = FTransform(rotate).TransformVector(moveDirection);
	this->Actor->AddMovementInput(moveDirection);
	moveDirection = FVector::ZeroVector;
}

