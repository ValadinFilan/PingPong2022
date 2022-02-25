// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerRocket.h"
#include "GameFramework/Pawn.h"	
//#include "Runtime/Networking/Public/Common/UdpSocketReceiver.h"
#include "Sockets/Public/IPAddress.h"
#include "Networking/Public/Common/UdpSocketReceiver.h"
#include "Networking/Public/Common/UdpSocketBuilder.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Endpoint.h"
#include "Async/Async.h"
#include "SocketSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CameraControlerPawn.generated.h"

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
	bool IsAIControllable = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerRocket> Rocket;

	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere)
	bool MouseMode = true;

	UPROPERTY(EditAnywhere)
	float RocketForce = 1;

	UPROPERTY(EditAnywhere)
	FVector HittingPoint = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FRotator AddedRotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere)
	FSensorData RocketData = FSensorData();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	APlayerRocket* ControlableRocket;
	
	FSocket* ReceiverSocket;
	FUdpSocketReceiver* UDPReceiver;
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

	bool StartReceiveSocket(const FString& InListenIP, const int32 InListenPort);
	
	void StopReceiveSocket();

	void ReceiveData(const FArrayReaderPtr& DataPtr, const FIPv4Endpoint& Endpoint);

	void UpdateRocket(const FSensorData* Data);
};