// Fill out your copyright notice in the Description page of Project Settings.

#include "../AI/AIPaddle.h"
#include "../../Ball/Ball.h"
#include "EngineUtils.h"


AAIPaddle::AAIPaddle()
{

}

void AAIPaddle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    //ACTOR ITERATOR LOOP
    for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        ABall* Ball = *ActorItr;

        if (Ball != nullptr)
        {
            SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, GetActorLocation().Y, Ball->GetActorLocation().Z), DeltaTime, 300.f));
        }
    }
}

void AAIPaddle::BeginPlay()
{
    Super::BeginPlay();  
}
