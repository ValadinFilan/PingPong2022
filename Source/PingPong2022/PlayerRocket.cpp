// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRocket.h"
#include "CameraControlerPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerRocket, All, All)

// Sets default values
APlayerRocket::APlayerRocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseRocketMesh");
	SetRootComponent(BaseMesh);
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void APlayerRocket::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetActorRotation();
	RotationPoint = GetActorLocation();

}

// Called every frame
void APlayerRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RocketVelocityVector = (GetActorLocation() - LastLocation);
	LastLocation = GetActorLocation();
	RocketRotationVelocityRotator = (GetActorRotation() - LastRotation);
	LastRotation = GetActorRotation();

}

void APlayerRocket::Move(FVector DeltaVector)
{
	AddActorWorldOffset(DeltaVector * MoveVelocity, true);
}

void APlayerRocket::RotateAroundRotatePoint()
{
	FVector Position = GetActorLocation();
	float RotateY = (FMath::Atan((RotationPoint.Y - Position.Y) / (RotationPoint.Z - Position.Z)) * 180 / 3.1415926535) + ((RotationPoint.Z - Position.Z < 0) ? 0 : 180);
	FRotator DeltaRotation = FRotator(0, 0, RotateY);
	if ((RotationPoint.Y - Position.Y) > 0)
		SetActorRotation(StartRotation + DeltaRotation + FRotator(-1 * HandRotationAngle, HandRotationAngle, 0));
	else
		SetActorRotation(StartRotation + DeltaRotation + FRotator(-1 * HandRotationAngle, -1 * HandRotationAngle, 0));
		
}

void APlayerRocket::Rotate(FRotator DeltaRotation)
{
	AddActorLocalRotation(DeltaRotation * RotationVelocity);
}

void APlayerRocket::SetRotation(FRotator Rotation)
{
	SetActorRotation(Rotation);
}

void APlayerRocket::SetArmRotation(float Degrees)
{
	HandRotationAngle += Degrees;
}

void APlayerRocket::SetRotationPoint(FVector Point)
{
	RotationPoint = Point;
}

FVector APlayerRocket::GetRocketVelocityVector()
{
	return RocketVelocityVector;
}

FVector APlayerRocket::GetRocketVelocityVector(FVector Point)
{
	FVector Value = RocketVelocityVector + (Point - GetActorLocation()).Size() * RocketRotationVelocityRotator.Vector() * 18 / 3.1415926535;
	return Value;
}

void APlayerRocket::SendControllerHittingResult(int32 Result)
{
	if (RocketController) {
		ACameraControlerPawn* CameraControlerPawn = Cast<ACameraControlerPawn>(RocketController);
		CameraControlerPawn->ReceiveHittingResult(Result);
	}
}

void APlayerRocket::RotateAR(FRotator Rotation)
{
	FQuat XRotation = FQuat(1, 0, 0, Rotation.GetComponentForAxis(EAxis::X));
	FQuat YRotation = FQuat(0, 1, 0, Rotation.GetComponentForAxis(EAxis::Y));
	FQuat ZRotation = FQuat(0, 0, 1, Rotation.GetComponentForAxis(EAxis::Z));
	SetActorRotation(FRotator(XRotation * YRotation * ZRotation));
}


