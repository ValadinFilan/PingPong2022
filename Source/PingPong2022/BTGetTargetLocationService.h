// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTGetTargetLocationService.generated.h"

/**
 * Service for finding point of collision of rocket and ball
 */
UCLASS()
class PINGPONG2022_API UBTGetTargetLocationService : public UBTService
{
	GENERATED_BODY()
public:
	//The newest point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Point1KeySelector;

	//The next point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Point2KeySelector;

	//The oldest point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Point3KeySelector;

	//The target point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector TargerPointKeySelector;

	//The ball selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BallKeySelector;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	//Returns the point of collision
	float GetYValueOfCrossing(float x, float x1, float x2, float y1, float y2) {
		return ((x - x1) * (y2 - y1) / (x2 - x1)) + y2;
	}
};
