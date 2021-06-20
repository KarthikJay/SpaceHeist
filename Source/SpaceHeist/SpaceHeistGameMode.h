// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceHeistGameMode.generated.h"

UCLASS(minimalapi)
class ASpaceHeistGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceHeistGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	void OnCreateSessionComplete(FName ServerName, bool Success);

protected:
	IOnlineSessionPtr ActiveSession;

	UFUNCTION(BlueprintCallable)
		void CreateServer();

	UFUNCTION(BlueprintCallable)
		void JoinServer();
};



