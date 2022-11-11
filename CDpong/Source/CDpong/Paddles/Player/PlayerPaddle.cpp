// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPaddle.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "../../Board/Board.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	CollisionBox->SetBoxExtent(FVector(100, 10, 100));
	CollisionBox->SetCollisionProfileName("BlockAllDynamic");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->GetBodyInstance()->bLockRotation = true;
	CollisionBox->GetBodyInstance()->bLockXTranslation = true;
	CollisionBox->GetBodyInstance()->bLockYTranslation = true;
	CollisionBox->SetNotifyRigidBodyCollision(true);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SetRootComponent(CollisionBox);

	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");
	PlayerSprite->SetupAttachment(RootComponent);
	PlayerSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CollisionBox->OnComponentHit.AddDynamic(this, &APlayerPaddle::OnHit);
	
	Speed = 2.5;

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

void APlayerPaddle::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA<class ABoard>())
		{

		}
	}
}

