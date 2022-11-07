// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class CDPONG_API ABoard : public AActor
{
	GENERATED_BODY()

public:
		UPROPERTY(VisibleAnywhere, Category = "Custom")
			class UCameraComponent* Camera;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
			TSubclassOf<class ABall> BallTemplate;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
			TSubclassOf<class APlayerPaddle> PlayerPaddleTemplate;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
			TSubclassOf<class AAIPaddle> AIPaddleTemplate;

		UPROPERTY(EditAnywhere, Category = "Actor Visual")
			class UPaperSpriteComponent* BoardSprite;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
			class UBoxComponent* LeftGoal;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
			class UBoxComponent* RightGoal;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
			class UBoxComponent* TopWall;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
			class UBoxComponent* BottomWall;
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
