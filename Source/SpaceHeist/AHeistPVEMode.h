#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AHeistPVEMode.generated.h"

UCLASS(config=Game)
class SPACEHEIST_API AHeistPVEMode : public AGameMode
{
	GENERATED_BODY()

public:
	AHeistPVEMode();

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	const uint8_t MaxNumPlayers = 5;
	TArray<class APlayerController*> PlayerControllerList;

};
