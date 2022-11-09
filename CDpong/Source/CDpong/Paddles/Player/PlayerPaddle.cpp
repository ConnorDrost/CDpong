// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPaddle.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	CollisionBox->SetBoxExtent(FVector(100, 10, 100));
	CollisionBox->SetCollisionProfileName("BlockAllDynamic");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CollisionBox->GetBodyInstance()->bLockRotation = true;
	CollisionBox->GetBodyInstance()->bLockXTranslation = true;
	CollisionBox->GetBodyInstance()->bLockYTranslation = true;
	CollisionBox->SetNotifyRigidBodyCollision(true);
	SetRootComponent(CollisionBox);

	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");
	PlayerSprite->SetupAttachment(RootComponent);
	PlayerSprite->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	Speed = 2.5;

	Tags.Add("Player");

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
		NewLocation = GetActorLocation() + (GetActorUpVector() * -Movement * Speed);
	}

	SetActorLocation(NewLocation);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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

