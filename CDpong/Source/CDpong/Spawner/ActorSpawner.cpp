// Fill out your copyright notice in the Description page of Project Settings.


#include "../Spawner/ActorSpawner.h"
#include "../Ball/Ball.h"
#include "Components/ArrowComponent.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPointComponent = CreateDefaultSubobject<UArrowComponent>
		(TEXT("SpawnPoint"));
	SpawnPointComponent->SetupAttachment(RootComponent);
	SpawnPointComponent->ArrowSize = 5.f;
	SpawnPointComponent->SetRelativeRotation(FRotator(50.f, 0.f, 0.f));
	SpawnPointComponent->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorSpawner::SpawnActor()
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
				FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
				UPrimitiveComponent* physicsComponent = SpawnedActor->GetPhysicsComponent();
				physicsComponent->AddForce(direction * 1000000, NAME_None, true);
			}
		}
	}
}



