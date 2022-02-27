// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "PlayerRocket.h"
#include "AIRocketController.h"

DEFINE_LOG_CATEGORY_STATIC(LogBall, All, All)

// Sets default values
ABallActor::ABallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseRocketMesh");
	SetRootComponent(BaseMesh);
	SetActorEnableCollision(true);
	if (BaseMesh) {
		BaseMesh->OnComponentHit.AddDynamic(this, &ABallActor::OnHit);
	}
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GravityEnabled) {
		//Calculating gravity
		VelocityVector += FVector::ZAxisVector * -10 * BallMass / 24;
		
		//Calculating air resistance
		VelocityVector += -1 * VelocityVector.GetSafeNormal() * VelocityVector.Size() * 3.1415926535 / BallMass * Radius * Radius * EnviromentDensity * Enviroment / 2;
	}
	AddActorWorldOffset(VelocityVector, true);
}

void ABallActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	VelocityVector = (VelocityVector.MirrorByVector(Hit.ImpactNormal));
	APlayerRocket* Rocket = Cast<APlayerRocket>(OtherActor);
	if (Rocket) {
		if (!GravityEnabled) {
			GravityEnabled = true;
		}
		VelocityVector += Hit.ImpactNormal * Rocket->RocketForce;
	}
}

FVector ABallActor::GetBallVelocity()
{
	return VelocityVector;
}

