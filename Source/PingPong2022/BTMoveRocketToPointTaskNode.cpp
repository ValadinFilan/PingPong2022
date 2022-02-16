// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControlerPawn.h"
#include "AIRocketController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTMoveRocketToPointTaskNode.h"

DEFINE_LOG_CATEGORY_STATIC(LogMoveRocketToPointTask, All, All)
//UE_LOG(LogMoveRocketToPointTask, Display, TEXT("Controller"));

EBTNodeResult::Type UBTMoveRocketToPointTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		AAIRocketController* Controller = Cast<AAIRocketController>(OwnerComp.GetAIOwner());
		if (Controller) {
			ACameraControlerPawn* Pawn = Cast<ACameraControlerPawn>(Controller->GetPawn());
			if (Pawn) {
				FVector Point1 = Blackboard->GetValueAsVector(TargetPoint.SelectedKeyName);
				FVector Vector = Point1 - Pawn->GetControlableRocket()->GetActorLocation();
				if (Vector.Size() > 5) {
					Vector = Vector / Vector.Size();
					Pawn->Move(Vector);
					ABallActor* Ball = Cast<ABallActor>(Blackboard->GetValueAsObject(BallKeySelector.SelectedKeyName));
					if (Ball) {
						if (((Ball->GetActorLocation() - Pawn->GetControlableRocket()->GetActorLocation()).Size() < 50)) {
							//GetHittingRotator(OwnerComp, Ball, Pawn);
							Pawn->HittingRotate();
						}
					}
					else {
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
void UBTMoveRocketToPointTaskNode::GetHittingRotator(UBehaviorTreeComponent& OwnerComp, ABallActor* Ball, ACameraControlerPawn* Pawn)
{
	AAIRocketController* Controller = Cast<AAIRocketController>(OwnerComp.GetAIOwner());
	FRotator Rotator = FRotator(0, 0, 0);
	float Force = 1.0f;
	if(Controller)
	{
		FVector Data = Controller->CalculateRotatingAndSpeedVector(Ball->GetBallVelocity());
		Rotator = FRotator(Data.Y, Data.X, 0);
		Force = Data.Z;
	}
	Pawn->SetRotation(Rotator);
	Pawn->GetControlableRocket()->SetForce(Force);
}