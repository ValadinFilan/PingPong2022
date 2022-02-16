// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "string"
#include "RocketAIPerceptionComponent.h"
#include "AIRocketController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG2022_API AAIRocketController : public AAIController
{
	GENERATED_BODY()
public: 
	AAIRocketController();

	UPROPERTY(EditAnywhere)
	URocketAIPerceptionComponent* RocketAIPerceptionComponent;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ReceiveHittingResult(int32 Result);
	FVector CalculateRotatingAndSpeedVector(FVector InputVector);
private:
	int32 n = -1;
};
