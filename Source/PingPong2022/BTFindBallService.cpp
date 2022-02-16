// Fill out your copyright notice in the Description page of Project Settings.

#include "BTFindBallService.h"
#include "AIRocketController.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBTFindBallService, All, All)

UBTFindBallService::UBTFindBallService()
{
	NodeName = "Find ball";
}

void UBTFindBallService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		AAIRocketController* Controller = Cast<AAIRocketController>(OwnerComp.GetAIOwner());
		if (Controller) {
			URocketAIPerceptionComponent* Perception = Controller->RocketAIPerceptionComponent;
			if (Perception) {
				Blackboard->SetValueAsObject(BallActorKey.SelectedKeyName, Perception->GetBall());
			}
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

