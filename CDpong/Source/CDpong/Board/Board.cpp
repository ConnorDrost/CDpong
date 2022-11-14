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
    TopWall->SetCollisionProfileName("BlockAllDynamic");
    TopWall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    TopWall->GetBodyInstance()->bLockRotation = true;
    TopWall->GetBodyInstance()->bLockTranslation = true;
    TopWall->SetSimulatePhysics(false);
    TopWall->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TopWall->SetupAttachment(RootComponent);

    BottomWall = CreateDefaultSubobject<UBoxComponent>("BW Collision Box");
    BottomWall->SetBoxExtent(FVector(500, 50, 10));
    BottomWall->SetCollisionProfileName("BlockAllDynamic");
    BottomWall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BottomWall->GetBodyInstance()->bLockRotation = true;
    BottomWall->GetBodyInstance()->bLockTranslation = true;
    BottomWall->SetSimulatePhysics(false);
    BottomWall->SetupAttachment(RootComponent);

    AIGoal = CreateDefaultSubobject<UBoxComponent>("RG Collision Box");
    AIGoal->SetBoxExtent(FVector(10, 50, 350));
    AIGoal->SetCollisionProfileName("OverlapAllDynamic");
    AIGoal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    AIGoal->GetBodyInstance()->bLockRotation = true;
    AIGoal->GetBodyInstance()->bLockTranslation = true;
    AIGoal->SetSimulatePhysics(false);
    AIGoal->SetupAttachment(RootComponent);

    PlayerGoal = CreateDefaultSubobject<UBoxComponent>("LG Collision Box");
    PlayerGoal->SetBoxExtent(FVector(10, 50, 350));
    PlayerGoal->SetCollisionProfileName("OverlapAllDynamic");
    PlayerGoal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    PlayerGoal->GetBodyInstance()->bLockRotation = true;
    PlayerGoal->GetBodyInstance()->bLockTranslation = true;
    PlayerGoal->SetSimulatePhysics(false);
    PlayerGoal->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(2000.0f);
    Camera->SetupAttachment(RootComponent);

    AIGoal->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);
    AIGoal->OnComponentEndOverlap.AddDynamic(this, &ABoard::EndOverlap);

    PlayerGoal->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);
    PlayerGoal->OnComponentEndOverlap.AddDynamic(this, &ABoard::EndOverlap);

    SpawnPointComponent = CreateDefaultSubobject<UArrowComponent>
        (TEXT("SpawnPoint"));
    SpawnPointComponent->ArrowSize = 5.f;
    SpawnPointComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    SpawnPointComponent->SetRelativeLocation(FVector(0.0f, 30.0f, 0.0f));
    SpawnPointComponent->SetupAttachment(RootComponent);

}

void ABoard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->IsA<ABall>())
        {

            AUEGameMode* gameMode = Cast<AUEGameMode>(GetWorld()->GetAuthGameMode());
            AUEGameState* gameState = gameMode->GetGameState<AUEGameState>();

            if (OverlappedComponent == AIGoal)
            {

                gameState->PlayerGoals++;

            }
            if (OverlappedComponent == PlayerGoal)
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
            SpawnActor();
        }
    }
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
    Super::BeginPlay();

    SpawnActor();
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

            FVector SpawnLocation = SpawnPointComponent->GetComponentLocation();
            FRotator SpawnRotation = FRotator(FMath::RandRange(30.f, -30.f), 0, 0);
            FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
            ABall* SpawnedActor = World->SpawnActor<ABall>(BallTemplate, SpawnTransform, SpawnParams);
        }
    }
}

