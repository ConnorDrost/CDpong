// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UEGameState.generated.h"

/**
 * 
 */
UCLASS()
class CDPONG_API AUEGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AUEGameState();

	UFUNCTION(BlueprintCallable, Category = "Pickups")
		int GetNumPlayerGoals() { return PlayerGoals; }

	UFUNCTION(BlueprintCallable, Category = "Pickups")
		int GetNumAIGoals() { return AIGoals; }

	float PlayerGoals;
	float AIGoals;

};
