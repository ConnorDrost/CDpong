// Fill out your copyright notice in the Description page of Project Settings.


#include "../Ball/Ball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("Projectile");
	CollisionSphere->SetSphereRadius(5.0f);
	CollisionSphere->SetCollisionProfileName("BlockAll");
	SetRootComponent(CollisionSphere);

	BallSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperFlipbookComponent"));
	BallSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallSprite->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovementComponent->InitialSpeed = 200.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->UpdatedComponent = CollisionSphere;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(CollisionSphere);
}

