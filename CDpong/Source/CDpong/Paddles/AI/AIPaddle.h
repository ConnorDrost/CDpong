// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Player/PlayerPaddle.h"
#include "AIPaddle.generated.h"

/**
 * 
 */
UCLASS()
class CDPONG_API AAIPaddle : public APlayerPaddle
{
	GENERATED_BODY()

public:

	AAIPaddle();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABall> BallTemplate;

protected:

	virtual void BeginPlay() override;
};
