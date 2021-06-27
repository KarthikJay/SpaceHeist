// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "HeistPVEGameState.generated.h"

/**
 *
 */
UCLASS(config=Game)
class SPACEHEIST_API AHeistPVEGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;


protected:

};
