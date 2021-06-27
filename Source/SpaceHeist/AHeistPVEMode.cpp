#include "AHeistPVEMode.h"
#include "SpaceHeistCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuHUD.h"
#include "MenuPlayerController.h"

AHeistPVEMode::AHeistPVEMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}

bool AHeistPVEMode::ReadyToStartMatch_Implementation()
{
	bool bReady = (Super::GetNumPlayers() >= 0 && Super::GetNumPlayers() < MaxNumPlayers) ? true : false;

	UE_LOG(LogTemp, Warning, TEXT("ReadyToStartMatch Values is: %s"), bReady ? TEXT("true") : TEXT("False"));

	return bReady;
}

void AHeistPVEMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerList.Add(NewPlayer);
}
