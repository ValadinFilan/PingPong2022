// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallActor.h"
#include "CameraControlerPawn.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTMoveRocketToPointTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG2022_API UBTMoveRocketToPointTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector RocketVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector TargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BallKeySelector;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void GetHittingRotator(UBehaviorTreeComponent& OwnerComp, ABallActor* Ball, ACameraControlerPawn* Pawn);
};
