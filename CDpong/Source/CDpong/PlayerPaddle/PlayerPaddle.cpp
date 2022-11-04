// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPaddle.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCollisionBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	PlayerCollisionBox->SetBoxExtent(FVector(100, 10, 100));
	PlayerCollisionBox->SetCollisionProfileName("BlockAllDynamic");
	PlayerCollisionBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	PlayerCollisionBox->GetBodyInstance()->bLockRotation = true;
	PlayerCollisionBox->GetBodyInstance()->bLockXTranslation = true;
	PlayerCollisionBox->GetBodyInstance()->bLockYTranslation = true;
	SetRootComponent(PlayerCollisionBox);

	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");
	PlayerSprite->SetupAttachment(RootComponent);
	PlayerSprite->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	Speed = 10;

}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	if (Movement != 0)
	{
		NewLocation = GetActorLocation() + (GetActorForwardVector() * -Movement * Speed);
	}

	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPaddle::Move(float value)
{
	Movement = value;
}

