// Fill out your copyright notice in the Description page of Project Settings.


#include "AITrainingGameModeBase.h"
#include <fstream>
#include <string>
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogAITrainingGameMode, All, All)

void AAITrainingGameModeBase::StartPlay()
{
    Super::StartPlay();
    States = 2 * NNormalDeltas * NNormalDeltas * 2 * NNormalDeltas * NBallSpeedDeltas;
    QVectorLength = States * NAnglesY * NAnglesZ * NRocketSpeedDeltas;
    StateLength = NAnglesY * NAnglesZ * NRocketSpeedDeltas;
    QVector = ReadVectorAsCSV("C:/temp/Matrix.txt", QVectorLength);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AAITrainingGameModeBase::OnTimerFired, TimerRate, true);

    UE_LOG(LogAITrainingGameMode, Display, TEXT("Training started %d"), QVectorLength)
}
void AAITrainingGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    SaveVectorAsCSV("C:/temp/Matrix.txt", QVector, QVectorLength);
}
void AAITrainingGameModeBase::SaveVectorAsCSV(std::string Path, int32* Vector, int32 Length)
{
    UE_LOG(LogAITrainingGameMode, Display, TEXT("CSV Saved"))
    std::fstream fout;
    fout.open(Path, std::ios::out);
    int32 sells = 0;
    if (fout) {
        for (int32 i = 0; i < QVectorLength; i++)
        {
            if (QVector[i] != 300) sells++;
            fout << QVector[i] << " ";
        }
        UE_LOG(LogAITrainingGameMode, Display, TEXT("Training completed: %d / %d"), sells, QVectorLength)
    }
    fout.close();
}
int32* AAITrainingGameModeBase::ReadVectorAsCSV(std::string Path, int32 Length)
{
    std::fstream fin;
    fin.open(Path, std::ios::in);
    int32* Vector = new int32[QVectorLength];
    if (fin) {
        for (int32 i = 0; i < QVectorLength; i++)
        {
            fin >> Vector[i];
        }
    }
    else {
        for (int32 i = 0; i < QVectorLength; i++)
            Vector[i] = 300;
    }
    fin.close();
    return Vector;
}
FVector AAITrainingGameModeBase::CalulateRotationAndSpeed(FVector Velocity, int32* n)
{
    return GetResult(GetState(Velocity), n);
}
int32 AAITrainingGameModeBase::GetState(FVector Velocity)
{
    int32 BottomBorder = 0;
    FVector NormalVector = Velocity.GetSafeNormal();
    if (Velocity.Y < 0) {

    }
    else {
        BottomBorder = States / 2;
    }
    if (Velocity.Z < 0) {

    }
    else {
        BottomBorder += States / 4;
    }
    int32 X = (int32)(FMath::Abs(NormalVector.X) * 10);
    int32 Y = (int32)(FMath::Abs(NormalVector.Y) * 10);
    int32 Z = (int32)(FMath::Abs(NormalVector.Z) * 10);
    BottomBorder += X * NNormalDeltas * NNormalDeltas * NBallSpeedDeltas;
    BottomBorder += Y * NNormalDeltas * NBallSpeedDeltas;
    BottomBorder += Z * NBallSpeedDeltas;
    if (Velocity.Size() < 50) {
        BottomBorder += ((int32)Velocity.Size()) % 10;
    }
    else {
        BottomBorder += 4;
    }
    return BottomBorder;
}
FVector AAITrainingGameModeBase::GetResult(int32 State, int32* n)
{
    int32 index = State * StateLength;
    int32 Result = index;
    int32 Weight = -1000;
    for (int32 i = index; i < index + StateLength; i++)
    {
        if (QVector[i] > Weight) {
            Weight = QVector[i];
            Result = i;
        }
    }
    int32 ResIndex = Result - index;
    FVector CalculatingResult = FVector(ResIndex % NAnglesY * AngleStep, -45 + ResIndex % NAnglesZ * AngleStep, 1 + (ResIndex % NRocketSpeedDeltas) / 10.0f);
    *n = Result;
    return CalculatingResult;
}
void AAITrainingGameModeBase::IndexateResult(int32 Result, int32 n)
{
    if (Result < 0) {
        QVector[n] += Result;
    }
    else {
        QVector[n] -= (Result - 100);
    }
    UE_LOG(LogAITrainingGameMode, Display, TEXT("Indexate result %d: %d"), n, Result)
}

void AAITrainingGameModeBase::OnTimerFired()
{
    SaveVectorAsCSV("C:/temp/Matrix.txt", QVector, QVectorLength);
}
