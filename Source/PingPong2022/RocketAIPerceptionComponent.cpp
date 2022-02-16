// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AIRocketController.h"

DEFINE_LOG_CATEGORY_STATIC(LogRocketAIPerceptionComponent, All, All)

ABallActor* URocketAIPerceptionComponent::GetBall() {
	AAIController* Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float Distance = MAX_FLT;
	ABallActor* NearestBall = nullptr;

	TArray<AActor*> PerceptedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceptedActors);
	for (AActor* PerceptedActor : PerceptedActors) {
		ABallActor* Ball = Cast<ABallActor>(PerceptedActor);
		if (Ball) {
			if (NearestBall) {
				if ((Ball->GetActorLocation() - Pawn->GetActorLocation()).Size() < Distance) {
					Distance = (Ball->GetActorLocation() - Pawn->GetActorLocation()).Size();
					NearestBall = Ball;
				}
			}
			else {
				NearestBall = Ball;
			}
		}
	}
	return NearestBall;
}
