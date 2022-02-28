// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRocket.h"
#include "CameraControlerPawn.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerRocket, All, All)

// Sets default values
APlayerRocket::APlayerRocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseRocketMesh");
	SetRootComponent(BaseMesh);
	MarkX = CreateDefaultSubobject<UStaticMeshComponent>("MarkX");
	MarkX->AttachTo(BaseMesh);
	MarkX->AddWorldOffset(FVector::XAxisVector * 250);
	MarkY = CreateDefaultSubobject<UStaticMeshComponent>("MarkY");
	MarkY->AttachTo(BaseMesh);
	MarkY->AddWorldOffset(FVector::YAxisVector * 250);
	MarkZ = CreateDefaultSubobject<UStaticMeshComponent>("MarkZ");
	MarkZ->AttachTo(BaseMesh);
	MarkZ->AddWorldOffset(FVector::ZAxisVector * 250);
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
	if (Rotation != FRotator::ZeroRotator) {
		FRotator Offset = Rotation;
		FQuat QuatRotation = FQuat(Offset);
		SetActorRotation(QuatRotation);
	}
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
	/*NOT DONE*/
	if (Rotation != FRotator::ZeroRotator) {
		/*
		if (FirstConnect) {
			FRotator XRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::XAxisVector, Rotation.Yaw);
			FRotator YRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::YAxisVector, Rotation.Roll);
			FRotator ZRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::ZAxisVector, Rotation.Pitch);
			BaseRotation = XRotation + ZRotation + YRotation;
			FirstConnect = false;
			UE_LOG(LogPlayerRocket, Display, TEXT("%d %d %d"), (int32)Rotation.Roll, (int32)Rotation.Yaw, (int32)Rotation.Pitch);
		}
		else
		{
			FRotator XRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::XAxisVector, Rotation.Yaw) * -1;
			FRotator YRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::YAxisVector, Rotation.Roll);
			FRotator ZRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::ZAxisVector, Rotation.Pitch);

			SetActorRotation(XRotation + ZRotation + YRotation - BaseRotation);
		}
		*/
		FRotator NewRotation = FRotator(-1 * Rotation.Roll - 90, 0, Rotation.Yaw - 90);
		//FRotator NewRotation = FRotator(-1 * Rotation.Roll - 90, Rotation.Roll, Rotation.Yaw - 90);

		//SetActorRotation(XRotation + ZRotation + YRotation - BaseRotation);
		SetActorRotation(NewRotation);
	}
}