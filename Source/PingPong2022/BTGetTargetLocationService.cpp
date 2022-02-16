// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGetTargetLocationService.h"
#include "CameraControlerPawn.h"
#include "AIRocketController.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBTGetTargetLocationService, All, All)

void UBTGetTargetLocationService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		AAIRocketController* Controller = Cast<AAIRocketController>(OwnerComp.GetAIOwner());
		if(Controller){
			ACameraControlerPawn* Pawn = Cast<ACameraControlerPawn>(Controller->GetPawn());
			if (Pawn) {
				FVector Point1 = Blackboard->GetValueAsVector(Point1KeySelector.SelectedKeyName);
				FVector Point2 = Blackboard->GetValueAsVector(Point2KeySelector.SelectedKeyName);
				FVector Point3 = Blackboard->GetValueAsVector(Point3KeySelector.SelectedKeyName);
				ABallActor* Ball = Cast<ABallActor>(Blackboard->GetValueAsObject(BallKeySelector.SelectedKeyName));
				if (Ball) {
					FVector IntersectPoint = FVector(Pawn->GetControlableRocket()->GetActorLocation().X, GetYValueOfCrossing(Pawn->GetControlableRocket()->GetActorLocation().X, Point1.X, Point2.X, Point1.Y, Point2.Y), Ball->GetActorLocation().Z);
					Blackboard->SetValueAsVector(TargerPointKeySelector.SelectedKeyName, IntersectPoint);
				}
			}
		}
	}
}


