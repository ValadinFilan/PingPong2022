// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "string"
#include "RocketAIPerceptionComponent.h"
#include "AIRocketController.generated.h"

/**
 * Rocket AI class
 */
UCLASS()
class PINGPONG2022_API AAIRocketController : public AAIController
{
	GENERATED_BODY()
public: 
	AAIRocketController();

	//Perception component for balls
	UPROPERTY(EditAnywhere)
	URocketAIPerceptionComponent* RocketAIPerceptionComponent;

	virtual void Tick(float DeltaTime) override;

	//Call back function for AI
	UFUNCTION(BlueprintCallable)
	void ReceiveHittingResult(int32 Result);

	//Calculating function for AI actions
	FVector CalculateRotatingAndSpeedVector(FVector InputVector);
private:
	//Weight for traing
	int32 n = -1;
};
