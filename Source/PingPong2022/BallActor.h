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

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector VelocityVector = FVector::XAxisVector * -5;

	UPROPERTY(EditAnywhere, Category = "Gravity")
		float BallMass = 0.02f;

	UPROPERTY(EditAnywhere, Category = "Gravity")
		float EnviromentDensity = 1.3f;

	UPROPERTY(EditAnywhere, Category = "Gravity")
		float Radius = 0.01f;

	UPROPERTY(EditAnywhere, Category = "Gravity")
		float Enviroment = 0.4f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool GravityEnabled = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable)
	FVector GetBallVelocity();
};
