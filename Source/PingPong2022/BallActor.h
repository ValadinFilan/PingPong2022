// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallActor.generated.h"

UCLASS()
class PINGPONG2022_API ABallActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallActor();

	//Ball mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh;

	//Ball velocity vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector VelocityVector = FVector::XAxisVector * -5;

	//Mass of ball
	UPROPERTY(EditAnywhere, Category = "Gravity")
		float BallMass = 0.02f;

	//Density of enviroment
	UPROPERTY(EditAnywhere, Category = "Gravity")
		float EnviromentDensity = 1.3f;

	//Radius of ball
	UPROPERTY(EditAnywhere, Category = "Gravity")
		float Radius = 0.01f;

	//Coefficient of enviroment for air resistance
	UPROPERTY(EditAnywhere, Category = "Gravity")
		float Enviroment = 0.4f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//If gravity enabled is true
	bool GravityEnabled = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Hit function
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	//Returns Ball velocity
	UFUNCTION(BlueprintCallable)
	FVector GetBallVelocity();
};
