// Fill out your copyright notice in the Description page of Project Settings.

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"

#include "../Ball/Ball.h"
#include "../PlayerPaddle/PlayerPaddle.h"
#include "../PlayerPaddle/AIPaddle.h"
#include "../Board/Board.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

