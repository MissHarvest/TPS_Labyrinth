// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EEnterType : uint8
{
	Normal,
	Edit,
};

UENUM(BlueprintType)
enum class EActorType : uint8
{
	PatrolPoint,
	Enemy,
	Chest,
};