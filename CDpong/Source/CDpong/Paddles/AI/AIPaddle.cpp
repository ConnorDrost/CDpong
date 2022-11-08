// Fill out your copyright notice in the Description page of Project Settings.

#include "../AI/AIPaddle.h"
#include "../../Ball/Ball.h"


AAIPaddle::AAIPaddle()
{
    Tags.Empty();

    Tags.Add("AIPaddle");
}

void AAIPaddle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Ball != nullptr)
    {
        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), Ball->GetActorLocation(), DeltaTime, 600.f));
    }
   
}

void AAIPaddle::SetBall(ABall* GameBall)
{
    Ball = GameBall;
}

void AAIPaddle::BeginPlay()
{
    Tags.Empty();

    Tags.Add("AIPaddle");

    Super::BeginPlay();
}
