// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerRocket.h"
#include "GameFramework/Pawn.h"
#include "CameraControlerPawn.generated.h"

UCLASS()
class PINGPONG2022_API ACameraControlerPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ACameraControlerPawn();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerRocket> Rocket;

	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere)
	bool MouseMode = true;

	UPROPERTY(EditAnywhere)
	FVector HittingPoint = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FRotator AddedRotation = FRotator::ZeroRotator;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APlayerRocket* ControlableRocket;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HitActionUp();
	void HitActionDown();
	void MoveX(float Amount);
	void MoveY(float Amount);
	void MoveZ(float Amount);
	void Move(FVector Vector);
	void MouseMoveX(float Amount);
	void MouseMoveY(float Amount);
	void SetRotation(float AmountX, float AmountY, float AmountZ);
	void SetRotation(FRotator Rotator);
	void RotateX(float Amount);
	void RotateY(float Amount);
	void RotateZ(float Amount);
	void HittingRotate();
	APlayerRocket* GetControlableRocket() { return ControlableRocket; }
	void ReceiveHittingResult(int32 Result);
};