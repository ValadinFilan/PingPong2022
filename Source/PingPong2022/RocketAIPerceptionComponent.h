// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallActor.h"
#include "Perception/AIPerceptionComponent.h"
#include "RocketAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG2022_API URocketAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public: 
	ABallActor* GetBall();
};
