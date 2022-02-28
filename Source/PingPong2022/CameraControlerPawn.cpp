// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraControlerPawn.h"
#include "Engine/World.h"
#include "AIRocketController.h"
#include "Components/SceneComponent.h"	
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Runtime/Networking/Public/Common/UdpSocketReceiver.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Endpoint.h"
#include "Async/Async.h"
#include "SocketSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Serialization/JsonSerializer.h"	


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
	const FVector NewLocation = GetActorLocation() + (FVector::XAxisVector * 100).RotateAngleAxis(GetActorRotation().GetComponentForAxis(EAxis::Z), FVector::ZAxisVector) + FVector::ZAxisVector * 50;
	const FRotator Rotation = GetActorRotation();
	if (World) {
		ControlableRocket = Cast<APlayerRocket>(World->SpawnActor(Rocket, &NewLocation, &Rotation));
		ControlableRocket->SetController(this);
		ControlableRocket->SetForce(RocketForce);
		if(Target) ControlableRocket->Target = Target;
	}
	if (!IsAIControllable) {
		StartReceiveSocket(TEXT("192.168.1.64"), 25565);
	}
}

// Called every frame
void ACameraControlerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!MouseMode) UpdateRocket(&RocketData);
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

void ACameraControlerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopReceiveSocket();
	Super::EndPlay(EndPlayReason);
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

void ACameraControlerPawn::SetARRotation(float AmountX, float AmountY, float AmountZ)
{
	FRotator Rotation = FRotator(AmountX, AmountY, AmountZ);
	if (ControlableRocket) {
		ControlableRocket->RotateAR(GetActorRotation() + Rotation);
	}
}

void ACameraControlerPawn::SetRotation(FRotator Rotator)
{
	if (ControlableRocket) {
		ControlableRocket->SetRotation(GetActorRotation() +Rotator);
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
	FRotator YRotation = FRotator(0, 1, 0) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Rotate(YRotation);
	}
}

void ACameraControlerPawn::RotateZ(float Amount)
{
	FRotator ZRotation = FRotator(0, 0, 1) * Amount;
	if (ControlableRocket) {
		ControlableRocket->Rotate(ZRotation);
	}
}

void ACameraControlerPawn::HittingRotate()
{
	FVector RocketPosition = ControlableRocket->GetActorLocation();
	FRotator RocketRotation = FRotator(15, FMath::RadiansToDegrees(FMath::Atan((RocketPosition.Y - HittingPoint.Y) / (RocketPosition.X - HittingPoint.X))), 0) + AddedRotation;
	ControlableRocket->SetRotation(GetActorRotation() + RocketRotation);
	ControlableRocket->RocketForce = 0.3f;
}

void ACameraControlerPawn::ReceiveHittingResult(int32 Result)
{
	AAIRocketController* AIController = Cast<AAIRocketController>(GetController());
	if (AIController) {
		AIController->ReceiveHittingResult(Result);
	}
}

bool ACameraControlerPawn::StartReceiveSocket(const FString& InListenIP, const int32 InListenPort)
{
	UE_LOG(LogCameraPawn, Display, TEXT("SOCKET STARTED"))
	FIPv4Address Addr;
	FIPv4Address::Parse(InListenIP, Addr);

	//Create Socket
	FIPv4Endpoint Endpoint(Addr, InListenPort);

	ReceiverSocket = FUdpSocketBuilder(TEXT("Rocket socket"))
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(2 * 1024 * 1024);

	FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(100);
	FString ThreadName = FString::Printf(TEXT("UDP RECEIVER-FUDPNative"));
	UDPReceiver = new FUdpSocketReceiver(ReceiverSocket, ThreadWaitTime, *ThreadName);

	UDPReceiver->OnDataReceived().BindLambda([this](const FArrayReaderPtr& DataPtr, const FIPv4Endpoint& Endpoint)
		{
			ReceiveData(DataPtr, Endpoint);
		});
	UDPReceiver->Start();

	return true;
}

void ACameraControlerPawn::ReceiveData(const FArrayReaderPtr& DataPtr, const FIPv4Endpoint& Endpoint)
{
	int32 Count = DataPtr->Num();
	const uint8* In = DataPtr.Get()->GetData();
	FString Result = "";

	while (Count)
	{
		int16 Value = *In;
		Result += TCHAR(Value);
		++In;
		Count--;
	}
	TSharedPtr<FJsonObject> MyJson = MakeShareable(new FJsonObject);
	if (DataPtr.Get()) {
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Result);
		if (FJsonSerializer::Deserialize(Reader, MyJson)) {
			RocketData.accel_freq = MyJson->GetNumberField(TEXT("accel_freq"));
			RocketData.accel_x = MyJson->GetNumberField(TEXT("accel_x"));
			RocketData.accel_y = MyJson->GetNumberField(TEXT("accel_y"));
			RocketData.accel_z = MyJson->GetNumberField(TEXT("accel_z"));
			RocketData.calibrate = MyJson->GetNumberField(TEXT("calibrate"));
			RocketData.gyro_azimuth = MyJson->GetNumberField(TEXT("gyro_azimuth"));
			RocketData.gyro_freq = MyJson->GetNumberField(TEXT("gyro_freq"));
			RocketData.gyro_pitch = MyJson->GetNumberField(TEXT("gyro_pitch"));
			RocketData.gyro_roll = MyJson->GetNumberField(TEXT("gyro_roll"));
			RocketData.timestamp = MyJson->GetNumberField(TEXT("timestamp"));
			MouseMode = false;
		}
		else {
			UE_LOG(LogCameraPawn, Display, TEXT("Can`t serialize"));
		}
	}
}

void ACameraControlerPawn::UpdateRocket(const FSensorData* Data)
{
	if (!MouseMode) {
		SetARRotation(Data->gyro_roll, Data->gyro_azimuth, Data->gyro_pitch);
		//MoveX(20 * Data->accel_x  / (2 * 24 * 24));
		//MoveY(20 * Data->accel_y  / (2 * 24 * 24));
		//MoveZ(20 * Data->accel_z  / (2 * 24 * 24));
	}
}

void ACameraControlerPawn::StopReceiveSocket()
{
	if (ReceiverSocket)
	{
		UDPReceiver->Stop();
		delete UDPReceiver;
		UDPReceiver = nullptr;
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ReceiverSocket);
		ReceiverSocket = nullptr;
	}
}


