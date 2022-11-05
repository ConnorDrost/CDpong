// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerController/UEPlayerController.h"
#include "../PlayerPaddle/PlayerPaddle.h"
#include "../PlayerState/UEPlayerState.h"

void AUEPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerPaddle = Cast<APlayerPaddle>(aPawn);

}

void AUEPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AUEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		InputComponent->BindAxis("Move", this, &AUEPlayerController::Move);
	}
}

void AUEPlayerController::Move(float value)
{
	if (PlayerPaddle)
	{
		PlayerPaddle->Move(value);
	}
}
