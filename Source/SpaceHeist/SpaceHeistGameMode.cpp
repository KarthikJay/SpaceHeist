// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceHeistGameMode.h"
#include "SpaceHeistCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/Class.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

ASpaceHeistGameMode::ASpaceHeistGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASpaceHeistGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	ActiveSession = IOnlineSubsystem::Get()->GetSessionInterface();
	// Bind Delegates here
	ActiveSession->OnCreateSessionCompleteDelegates.AddUObject(this, &ASpaceHeistGameMode::OnCreateSessionComplete);
	
}

void ASpaceHeistGameMode::OnCreateSessionComplete(FName ServerName, bool Success) {
	UE_LOG(LogOnline, Warning, TEXT("OnCreateSessionComplete was called! Success: %d"), Success)
	if (Success)
	{
		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap.ThirdPersonExampleMap?listen");
	}
}

void ASpaceHeistGameMode::CreateServer()
{
	FOnlineSessionSettings CurrentSessionSettings;
	CurrentSessionSettings.bAllowJoinInProgress = true;
	CurrentSessionSettings.bShouldAdvertise = true;
	CurrentSessionSettings.bUsesPresence = true;
	CurrentSessionSettings.NumPublicConnections = 5;

	ActiveSession->CreateSession(0, FName("KJ Session"), CurrentSessionSettings);
}

void ASpaceHeistGameMode::JoinServer() {
	
}
