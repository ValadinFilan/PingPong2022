// Fill out your copyright notice in the Description page of Project Settings.


DEFINE_LOG_CATEGORY_STATIC(LogAIRocketController, All, All)
//UE_LOG(LogAIRocketController, Display, TEXT("No"));

#include "AIRocketController.h"
#include "AITrainingGameModeBase.h"
#include "CameraControlerPawn.h"
AAIRocketController::AAIRocketController() {
	RocketAIPerceptionComponent = CreateDefaultSubobject<URocketAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*RocketAIPerceptionComponent);
}

void AAIRocketController::Tick(float DeltaTime)
{

}

void AAIRocketController::ReceiveHittingResult(int32 Result)
{
	AAITrainingGameModeBase* AIGameMode = Cast<AAITrainingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (AIGameMode) {
		AIGameMode->IndexateResult(Result, n);
		n = -1;
	}
}

FVector AAIRocketController::CalculateRotatingAndSpeedVector(FVector InputVector)
{
	AAITrainingGameModeBase* AIGameMode = Cast<AAITrainingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (AIGameMode) {
		return AIGameMode->CalulateRotationAndSpeed(InputVector, &n);
	}
	else {
		return FVector(0, 0, 1);
	}
}

