// Fill out your copyright notice in the Description page of Project Settings.


#include "../Ball/Ball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"

#include "../Paddles/Player/PlayerPaddle.h"
#include "../Paddles/AI/AIPaddle.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("Projectile");
	CollisionSphere->SetSphereRadius(5.0f);
	CollisionSphere->SetCollisionProfileName("BlockAll");
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->GetBodyInstance()->bLockRotation = true;
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABall::OnHit);
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetEnableGravity(false);
	SetRootComponent(CollisionSphere);

	BallSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperFlipbookComponent"));
	BallSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallSprite->GetBodyInstance()->bLockRotation = true;
	BallSprite->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovementComponent->InitialSpeed = 600.f;
	ProjectileMovementComponent->MaxSpeed = 10000000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->Bounciness = 1.f;
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

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA<class AAIPaddle>())
		{
			/*FVector direction = FRotationMatrix(CollisionSphere->GetComponentTransform().Rotator()).GetScaledAxis(EAxis::Y);
			CollisionSphere->GetBodyInstance()->AddForce(direction * 10000000, NAME_None, true);
			ProjectileMovementComponent->UpdatedComponent = CollisionSphere;*/
		}	
	}
}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(CollisionSphere);
}

