// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CDPONG_API AUEPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(float value);

	class AUEPlayerState* PlayerState;
	class APlayerPaddle* PlayerPaddle;
	
};
