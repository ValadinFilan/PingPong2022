// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallActor.h"
#include "CameraControlerPawn.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTMoveRocketToPointTaskNode.generated.h"

/**
 * Task node for moving rocket to target point
 */
UCLASS()
class PINGPONG2022_API UBTMoveRocketToPointTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	//Rocket velocity key selector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector RocketVelocity;

	//The target point key selector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector TargetPoint;

	//The ball key selector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BallKeySelector;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void GetHittingRotator(UBehaviorTreeComponent& OwnerComp, ABallActor* Ball, ACameraControlerPawn* Pawn);
};
