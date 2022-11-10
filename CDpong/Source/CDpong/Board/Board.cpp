// Fill out your copyright notice in the Description page of Project Settings.

#include "../Board/Board.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "DrawDebugHelpers.h"

#include "../Ball/Ball.h"
#include "../Paddles/Player/PlayerPaddle.h"
#include "../Paddles/AI/AIPaddle.h"
#include "../GameMode/UEGameMode.h"
#include "../GameState/UEGameState.h"

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
	TopWall->SetCollisionProfileName("BlockAll");
	TopWall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TopWall->GetBodyInstance()->bLockRotation = true;
	TopWall->GetBodyInstance()->bLockTranslation = true;
	TopWall->SetSimulatePhysics(false);
	TopWall->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	TopWall->SetupAttachment(RootComponent);

	BottomWall = CreateDefaultSubobject<UBoxComponent>("BW Collision Box");
	BottomWall->SetBoxExtent(FVector(500, 50, 10));
	BottomWall->SetCollisionProfileName("BlockAll");
	BottomWall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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

	RightGoal->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);
	RightGoal->OnComponentEndOverlap.AddDynamic(this, &ABoard::EndOverlap);

	LeftGoal->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);
	LeftGoal->OnComponentEndOverlap.AddDynamic(this, &ABoard::EndOverlap);

	SpawnPointComponent = CreateDefaultSubobject<UArrowComponent>
		(TEXT("SpawnPoint"));
	SpawnPointComponent->SetupAttachment(RootComponent);
	SpawnPointComponent->ArrowSize = 5.f;
	SpawnPointComponent->SetRelativeRotation(FRotator(50.f, 0.f, 0.f));
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

void ABoard::SpawnActor()
{
	if (BallTemplate != nullptr)
	{
		UWorld* World = GetWorld();
		
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			FTransform SpawnTransform = SpawnPointComponent->GetComponentTransform();
			ABall* SpawnedActor = World->SpawnActor<ABall>(BallTemplate, SpawnTransform, SpawnParams);

			if (SpawnedActor)
			{
				FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::Y);
				UPrimitiveComponent* physicsComponent = SpawnedActor->GetPhysicsComponent();
				physicsComponent->AddForce(direction * 100, NAME_None, true);
			}
		}
	}
}

