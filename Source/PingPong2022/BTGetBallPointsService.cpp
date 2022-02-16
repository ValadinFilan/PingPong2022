// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGetBallPointsService.h"
#include "AIRocketController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTGetBallPointsService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		ABallActor* Ball = Cast<ABallActor>(Blackboard->GetValueAsObject(BallKeySelector.SelectedKeyName));
		if (Ball) {
			FVector Point1 = Blackboard->GetValueAsVector(Point1KeySelector.SelectedKeyName);
			FVector Point2 = Blackboard->GetValueAsVector(Point2KeySelector.SelectedKeyName);
			FVector Point3 = Blackboard->GetValueAsVector(Point3KeySelector.SelectedKeyName);

			Blackboard->SetValueAsVector(Point1KeySelector.SelectedKeyName, Point2);
			Blackboard->SetValueAsVector(Point2KeySelector.SelectedKeyName, Point3);
			Blackboard->SetValueAsVector(Point3KeySelector.SelectedKeyName, Ball->GetActorLocation());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
