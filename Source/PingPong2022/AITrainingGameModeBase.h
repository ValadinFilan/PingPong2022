// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <string>
#include "AITrainingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG2022_API AAITrainingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void StartPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SaveVectorAsCSV(std::string Path, int32* Vector, int32 Length);
	int32* ReadVectorAsCSV(std::string Path, int32 Length);
	FVector CalulateRotationAndSpeed(FVector Velocity, int32* n);
	int32 GetState(FVector Velocity);
	FVector GetResult(int32 State, int32* n);
	void IndexateResult(int32 Result, int32 n);
	void OnTimerFired();
private:
	int32* QVector;
	int32 QVectorLength;
	int32 States;
	int32 StateLength;
	float TimerRate = 1800.0f;
	const int32 AngleStep = 10;
	const int32 NNormalDeltas = 11;
	const int32 NBallSpeedDeltas = 5;
	const int32 NAnglesY = 180 / AngleStep + 1;
	const int32 NAnglesZ = 90 / AngleStep + 1;
	const int32 NRocketSpeedDeltas = 5;

	FTimerHandle TimerHandle;
	
};
