// Fill out your copyright notice in the Description page of Project Settings.

#include "../Board/Board.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"

#include "../Ball/Ball.h"
#include "../Paddles/Player/PlayerPaddle.h"
#include "../Paddles/AI/AIPaddle.h"
#include "../GameMode/UEGameMode.h"
#include "../GameState/UEGameState.h"
#include "../Spawner/\ActorSpawner.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoardSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual");
	BoardSprite->SetCollisionProfileName("NoCollision");
	BoardSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoardSprite->SetGenerateOverlapEvents(false);
	
	SetRootComponent(BoardSprite);

	TopWall = CreateDefaultSubobject<UBoxComponent>("TW Collision Box");
	TopWall->SetBoxExtent(FVector(500, 50, 10));
	TopWall->SetCollisionProfileName("BlockAllDynamic");
	TopWall->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	TopWall->GetBodyInstance()->bLockRotation = true;
	TopWall->GetBodyInstance()->bLockTranslation = true;
	TopWall->SetSimulatePhysics(false);
	TopWall->SetupAttachment(RootComponent);

	BottomWall = CreateDefaultSubobject<UBoxComponent>("BW Collision Box");
	BottomWall->SetBoxExtent(FVector(500, 50, 10));
	BottomWall->SetCollisionProfileName("BlockAllDynamic");
	BottomWall->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	BottomWall->GetBodyInstance()->bLockRotation = true;
	BottomWall->GetBodyInstance()->bLockTranslation = true;
	BottomWall->SetSimulatePhysics(false);
	BottomWall->SetupAttachment(RootComponent);

	RightGoal = CreateDefaultSubobject<UBoxComponent>("RG Collision Box");
	RightGoal->SetBoxExtent(FVector(10, 50, 350));
	RightGoal->SetCollisionProfileName("OverlapAllDynamic");
	RightGoal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightGoal->GetBodyInstance()->bLockRotation = true;
	RightGoal->GetBodyInstance()->bLockTranslation = true;
	RightGoal->SetSimulatePhysics(false);
	RightGoal->SetupAttachment(RootComponent);

	LeftGoal = CreateDefaultSubobject<UBoxComponent>("LG Collision Box");
	LeftGoal->SetBoxExtent(FVector(10, 50, 350));
	LeftGoal->SetCollisionProfileName("OverlapAllDynamic");
	LeftGoal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftGoal->GetBodyInstance()->bLockRotation = true;
	LeftGoal->GetBodyInstance()->bLockTranslation = true;
	LeftGoal->SetSimulatePhysics(false);
	LeftGoal->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	Camera->SetOrthoWidth(2000.0f);
	Camera->SetupAttachment(RootComponent);
}

void ABoard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA<ABall>())
		{
			AUEGameMode* gameMode = Cast<AUEGameMode>(GetWorld()->GetAuthGameMode());
			AUEGameState* gameState = gameMode->GetGameState<AUEGameState>();

			if (goal == EGoal::RIGHT)
			{
				gameState->PlayerGoals++;
			}
			else
			{
				gameState->AIGoals++;
			}

			OtherActor->Destroy();
		}
	}
}

void ABoard::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA<ABall>())
		{
			OtherActor->Destroy();
		}
	}
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

