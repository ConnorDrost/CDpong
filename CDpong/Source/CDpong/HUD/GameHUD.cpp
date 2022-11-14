// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AGameHUD::AGameHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/UI/WBP_PlayerUI"));

    if (playerHud.Succeeded())
    {
        PlayerGuiClass = playerHud.Class;
    }
   
}
void AGameHUD::BeginPlay()
{
    PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(), PlayerGuiClass);
    PlayerGui->AddToViewport();

}