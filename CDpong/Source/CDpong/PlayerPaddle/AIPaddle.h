// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PlayerPaddle/PlayerPaddle.h"
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

	

protected:

	virtual void BeginPlay() override;

	void SetBall(ABall* GameBall);

	class ABall* Ball;

	
};
