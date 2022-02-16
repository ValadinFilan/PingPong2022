// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerRocket.generated.h"

UCLASS()
class PINGPONG2022_API APlayerRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerRocket();

	UPROPERTY(EditAnywhere)
	float MoveVelocity = 10;

	UPROPERTY(EditAnywhere)
	float RotationVelocity = 1;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RocketForce = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector RotationPoint;
	FRotator StartRotation;
	FRotator HittingDeltaRotation = FRotator(0, 0, 0);
	float HandRotationAngle = 0; 
	FVector RocketVelocityVector = FVector::ZeroVector;
	FRotator RocketRotationVelocityRotator = FRotator::ZeroRotator;
	FVector  LastLocation = FVector::ZeroVector;
	FRotator LastRotation = FRotator::ZeroRotator;
	APawn* RocketController;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Move(FVector DeltaVector);
	void RotateAroundRotatePoint();
	void Rotate(FRotator DeltaRotation);
	void SetRotation(FRotator Rotation);
	void SetArmRotation(float Degrees);
	void SetRotationPoint(FVector Point);
	FVector GetRocketVelocityVector();
	FVector GetRocketVelocityVector(FVector Point);
	void SetController(APawn* Controller) {
		this->RocketController = Controller;
	}
	void SetForce(float Force) {
		if (Force >= 1) {
			this->RocketForce = Force;
		}
	}
	float GetForce() {
		return RocketForce;
	}
	UFUNCTION(BlueprintCallable)
	void SendControllerHittingResult(int32 Result);
};
