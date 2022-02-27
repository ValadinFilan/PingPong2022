// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerRocket.h"
#include "GameFramework/Pawn.h"	
#include "Sockets/Public/IPAddress.h"
#include "Networking/Public/Common/UdpSocketReceiver.h"
#include "Networking/Public/Common/UdpSocketBuilder.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Endpoint.h"
#include "Async/Async.h"
#include "SocketSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CameraControlerPawn.generated.h"

/*
	Structure for received data from controller
*/
USTRUCT()
struct FSensorData {
	GENERATED_USTRUCT_BODY()
	float gyro_azimuth = 0;
	float gyro_pitch = 0;
	float gyro_roll = 0;
	float gyro_freq = 0;

	float accel_x = 0;
	float accel_y = 0;
	float accel_z = 0;
	float accel_freq = 0;

	long timestamp = 0;

	int calibrate = 0;
};
/*
	Class of main player controller
*/
UCLASS()
class PINGPONG2022_API ACameraControlerPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ACameraControlerPawn();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	//Is true when controlled by AI
	UPROPERTY(EditAnywhere)
	bool IsAIControllable = false;

	//The rocket actor
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerRocket> Rocket;

	//Target for training
	UPROPERTY(EditAnywhere)
	AActor* Target;

	//Is true when player uses mouse as controller
	UPROPERTY(EditAnywhere)
	bool MouseMode = true;

	//Force of rocket hit
	UPROPERTY(EditAnywhere)
	float RocketForce = 1;

	//Pint forr targeting
	UPROPERTY(EditAnywhere)
	FVector HittingPoint = FVector::ZeroVector;

	//Start rotation
	UPROPERTY(EditAnywhere)
	FRotator AddedRotation = FRotator::ZeroRotator;

	//Received data from controller
	UPROPERTY(VisibleAnywhere)
	FSensorData RocketData = FSensorData();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//The controlled rocket actor
	APlayerRocket* ControlableRocket;

	//Socket for receiving data
	FSocket* ReceiverSocket;

	//Udp socket for receiving data
	FUdpSocketReceiver* UDPReceiver;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///////////////////// MOVING API

	//Mouse wheel up
	void HitActionUp();

	//Mouse wheel down
	void HitActionDown();

	//Mouse move X function
	void MouseMoveX(float Amount);

	//Mouse move Y function
	void MouseMoveY(float Amount);

	//Move rocket on X vector by value
	void MoveX(float Amount);

	//Move rocket on Y vector by value
	void MoveY(float Amount);

	//Move rocket on Z vector by value
	void MoveZ(float Amount);

	//Move rocket on vector
	void Move(FVector Vector);

	//Set rocket rotation by received data
	void SetARRotation(float AmountX, float AmountY, float AmountZ);

	//Set rocket roatation by FRotator
	void SetRotation(FRotator Rotator);

	//Rotate on X rotator by value
	void RotateX(float Amount);

	//Rotate on Y rotator by value
	void RotateY(float Amount);

	//Rotate on Z rotator by value
	void RotateZ(float Amount);

	//Rotate rocket for hitting to hitting point
	void HittingRotate();

	//Returns controled rocket
	APlayerRocket* GetControlableRocket() { return ControlableRocket; }

	//Receive result of action
	void ReceiveHittingResult(int32 Result);

	//Start UPD socket for receiving
	bool StartReceiveSocket(const FString& InListenIP, const int32 InListenPort);


	//Stop UPD socket
	void StopReceiveSocket();

	//Process received data
	void ReceiveData(const FArrayReaderPtr& DataPtr, const FIPv4Endpoint& Endpoint);

	//Update rocket position
	void UpdateRocket(const FSensorData* Data);
};