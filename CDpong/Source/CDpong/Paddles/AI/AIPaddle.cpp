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

    if (BallTemplate != nullptr)
    {
        //SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), BallTemplate->GetActorLocation(), DeltaTime, 600.f));
    }
   
}

void AAIPaddle::BeginPlay()
{
    Tags.Empty();

    Tags.Add("AIPaddle");

    Super::BeginPlay();

   
}
