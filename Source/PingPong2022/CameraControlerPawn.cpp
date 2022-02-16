// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraControlerPawn.h"
#include "Engine/World.h"
#include "AIRocketController.h"
#include "Components/SceneComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogCameraPawn, All, All)

// Sets default values
ACameraControlerPawn::ACameraControlerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ACameraControlerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	const FVector NewLocation = GetActorLocation() + (FVector::XAxisVector * 100).RotateAngleAxis(GetActorRotation().GetComponentForAxis(EAxis::Z), FVector::ZAxisVector);
	const FRotator Rotation = GetActorRotation();
	if (World) {
		ControlableRocket = Cast<APlayerRocket>(World->SpawnActor(Rocket, &NewLocation, &Rotation));
		ControlableRocket->SetController(this);
		ControlableRocket->SetForce(RocketForce);
		if(Target) ControlableRocket->Target = Target;
	}
}

// Called every frame
void ACameraControlerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACameraControlerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseMoveX", this, &ACameraControlerPawn::MouseMoveX);

	PlayerInputComponent->BindAxis("MouseMoveY", this, &ACameraControlerPawn::MouseMoveY);
	
	PlayerInputComponent->BindAction("WheelScrollUp", EInputEvent::IE_Released,this, &ACameraControlerPawn::HitActionUp);
	PlayerInputComponent->BindAction("WheelScrollDown", EInputEvent::IE_Released, this, &ACameraControlerPawn::HitActionDown);

}

void ACameraControlerPawn::HitActionUp()
{
	ControlableRocket->SetArmRotation(1);
}
void ACameraControlerPawn::HitActionDown()
{
	ControlableRocket->SetArmRotation(-1);
}

void ACameraControlerPawn::MoveX(float Amount)
{
	FVector XVector = FVector(1, 0, 0) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Move(XVector);
	}
}

void ACameraControlerPawn::MoveY(float Amount)
{
	FVector YVector = FVector(0, 1, 0) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Move(YVector);
	}
}

void ACameraControlerPawn::MoveZ(float Amount)
{
	FVector ZVector = FVector(0, 0, 1) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Move(ZVector);
	}
}

void ACameraControlerPawn::Move(FVector Vector)
{
	MoveX(Vector.X);
	MoveY(Vector.Y);
	MoveZ(Vector.Z);
}

void ACameraControlerPawn::MouseMoveX(float Amount)
{
	if (MouseMode) {
		FVector YVector = FVector(0, 1, 0) * Amount;
		FVector OffsetVector = YVector.RotateAngleAxis(GetActorRotation().GetComponentForAxis(EAxis::Z), FVector::ZAxisVector);
		if (ControlableRocket) {
			ControlableRocket->Move(OffsetVector);
			ControlableRocket->RotateAroundRotatePoint();
		}
	}
}

void ACameraControlerPawn::MouseMoveY(float Amount)
{
	if (MouseMode) {
		FVector ZVector = FVector(0, 0, 1) * Amount;
		if (ControlableRocket) {
			ControlableRocket->Move(ZVector);
			ControlableRocket->RotateAroundRotatePoint();
		}
	}
}

void ACameraControlerPawn::SetRotation(float AmountX, float AmountY, float AmountZ)
{
	FRotator Rotation = FRotator(AmountX, AmountY, AmountZ);
	if (ControlableRocket) {
		ControlableRocket->SetRotation(GetActorRotation() + Rotation);
	}
}

void ACameraControlerPawn::SetRotation(FRotator Rotator)
{
	if (ControlableRocket) {
		ControlableRocket->SetRotation(GetActorRotation() + Rotator);
	}
}

void ACameraControlerPawn::RotateX(float Amount)
{
	FRotator XRotation = FRotator(1, 0, 0) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Rotate(XRotation);
	}
}

void ACameraControlerPawn::RotateY(float Amount)
{
	FRotator XRotation = FRotator(0, 1, 0) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Rotate(XRotation);
	}
}

void ACameraControlerPawn::RotateZ(float Amount)
{
	FRotator XRotation = FRotator(0, 0, 1) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Rotate(XRotation);
	}
}

void ACameraControlerPawn::HittingRotate()
{
	FVector RocketPosition = ControlableRocket->GetActorLocation();
	FRotator RocketRotation = FRotator(0, FMath::RadiansToDegrees(FMath::Atan((RocketPosition.Y - HittingPoint.Y) / (RocketPosition.X - HittingPoint.X))), 0) + AddedRotation;
	ControlableRocket->SetRotation(GetActorRotation() + RocketRotation);
}

void ACameraControlerPawn::ReceiveHittingResult(int32 Result)
{
	AAIRocketController* AIController = Cast<AAIRocketController>(GetController());
	if (AIController) {
		AIController->ReceiveHittingResult(Result);
	}
}

