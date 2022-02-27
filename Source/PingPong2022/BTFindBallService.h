// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "BTFindBallService.generated.h"

/**
 * Service for finding ball
 */
UCLASS()
class PINGPONG2022_API UBTFindBallService : public UBTService
{
	GENERATED_BODY()
public:
	UBTFindBallService();

	//Celector key for found ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BallActorKey;

	//Finding ball finction
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
