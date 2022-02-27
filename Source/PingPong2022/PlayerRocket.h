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

	//Rocket move velocity value
	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveVelocity = 10;

	//Rocket rotation velocity value
	UPROPERTY(EditAnywhere, Category = "Move")
	float RotationVelocity = 1;

	//Default rotation
	UPROPERTY(EditAnywhere, Category = "Move")
	FRotator BaseRotation = FRotator::ZeroRotator;

	//Rocket mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	//Mark for calculating relative X vector
	UPROPERTY(EditAnywhere, Category = "ARMove")
	UStaticMeshComponent* MarkX;

	//Mark for calculating relative Y vector
	UPROPERTY(EditAnywhere, Category = "ARMove")
	UStaticMeshComponent* MarkY;

	//Mark for calculating relative Z vector
	UPROPERTY(EditAnywhere, Category = "ARMove")
	UStaticMeshComponent* MarkZ;


	//Default calibrate rotator
	UPROPERTY(EditAnywhere, Category = "Move")
	FRotator BaseARRotation = FRotator::ZeroRotator;

	//Target fot hitting
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* Target;

	//Force of the rocket
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RocketForce = 7;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Point of auto rotating
	FVector RotationPoint;

	//Default rotation
	FRotator StartRotation;

	//Hitting totation
	FRotator HittingDeltaRotation = FRotator(0, 0, 0);

	//Rotating angle constraint value
	float HandRotationAngle = 0;

	//Rocket velocity vector
	FVector RocketVelocityVector = FVector::ZeroVector;

	//Rocket rotating velocity vector
	FRotator RocketRotationVelocityRotator = FRotator::ZeroRotator;

	//Last rocket location
	FVector  LastLocation = FVector::ZeroVector;

	//Last rocket rotation
	FRotator LastRotation = FRotator::ZeroRotator;

	//Controller
	APawn* RocketController;

	//Is first connection to controller
	bool FirstConnect = true;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Move rocket on vector
	void Move(FVector DeltaVector);

	//Auto rotate around point
	void RotateAroundRotatePoint();

	//Rotate rocket on rottor
	void Rotate(FRotator DeltaRotation);

	//Set rocket rotation
	void SetRotation(FRotator Rotation);

	//Setter for arm rotation
	void SetArmRotation(float Degrees);

	//Setter of rotating point
	void SetRotationPoint(FVector Point);

	//Returns moving speed
	FVector GetRocketVelocityVector();

	//Returns moving speed plus rotation linear speed in point
	FVector GetRocketVelocityVector(FVector Point);


	//Setter for controler
	void SetController(APawn* Controller) {
		this->RocketController = Controller;
	}

	//Setter fot force
	void SetForce(float Force) {
		if (Force >= 1) {
			this->RocketForce = Force;
		}
	}

	//Returns force of rocket
	float GetForce() {
		return RocketForce;
	}

	//Send to controller result of hitting 
	UFUNCTION(BlueprintCallable)
	void SendControllerHittingResult(int32 Result);

	//AR rotation by controller data
	void RotateAR(FRotator Rotation);
};
