#include "AIRocketController.h"
#include "AITrainingGameModeBase.h"
#include "CameraControlerPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIRocketController, All, All)

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
		//Sending message for training AI about result of action
		AIGameMode->IndexateResult(Result, n);
		n = -1;
	}
}

FVector AAIRocketController::CalculateRotatingAndSpeedVector(FVector InputVector)
{
	AAITrainingGameModeBase* AIGameMode = Cast<AAITrainingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (AIGameMode) {
		//Get action from AI algorithm 
		return AIGameMode->CalulateRotationAndSpeed(InputVector, &n);
	}
	else {
		//Default action
		return FVector(0, 0, 0);
	}
}

