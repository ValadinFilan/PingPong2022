// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <string>
#include "AITrainingGameModeBase.generated.h"

/**
 * Gamemodeclass for trainging AI
 */
UCLASS()
class PINGPONG2022_API AAITrainingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	/** Transitions to calls BeginPlay on actors. */
	virtual void StartPlay() override;

	//Call in the end of game
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//Save QVector to CSV file
	void SaveVectorAsCSV(std::string Path, int32* Vector, int32 Length);

	//Read QVector from CSV file
	int32* ReadVectorAsCSV(std::string Path, int32 Length);

	//Returns result of QLearning Algorithm
	FVector CalulateRotationAndSpeed(FVector Velocity, int32* n);

	//Returns state for QLearning
	int32 GetState(FVector Velocity);

	//Calculate result of QLearning Algorithm
	FVector GetResult(int32 State, int32* n);

	//Processes results of actions
	void IndexateResult(int32 Result, int32 n);

	//Timer for auto saving vector
	void OnTimerFired();
private:
	//Vector of weights
	int32* QVector;

	//QVector size
	int32 QVectorLength;

	//Count of states
	int32 States;

	//Count of variants in one state
	int32 StateLength;

	//Auto saving time rate
	float TimerRate = 1800.0f;

	//Step of angle calculating
	const int32 AngleStep = 10;

	//Count of variants of normal
	const int32 NNormalDeltas = 11;

	//Count of variants of rocket speed
	const int32 NBallSpeedDeltas = 5;

	//Count of variants of Y angles
	const int32 NAnglesY = 180 / AngleStep + 1;

	//Count of variants of Y angles
	const int32 NAnglesZ = 90 / AngleStep + 1;

	//Count of variants of Y angles
	const int32 NRocketSpeedDeltas = 5;

	//Timer handle
	FTimerHandle TimerHandle;
	
};
