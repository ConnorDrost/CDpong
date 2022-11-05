#include "UEGameMode.h"
#include "Kismet/GameplayStatics.h"

void AUEGameMode::BeginPlay()
{
	Super::BeginPlay();

	FString command = "show collision";

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (controller)
	{
		controller->ConsoleCommand(command, false);
		controller->bShowMouseCursor = true;
		controller->bEnableClickEvents = true;
		controller->bEnableMouseOverEvents = true;
	}
}
