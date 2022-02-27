// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTGetBallPointsService.generated.h"

/**
 * Service for ball tracing
 */
UCLASS()
class PINGPONG2022_API UBTGetBallPointsService : public UBTService
{
	GENERATED_BODY()
public:
	//The newest point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Point1KeySelector;

	//Next point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Point2KeySelector;

	//The oldes point selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector Point3KeySelector;

	//Ball selector key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BallKeySelector;

	//Update ball trace line
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
