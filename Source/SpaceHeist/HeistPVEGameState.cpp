#include "HeistPVEGameState.h"
#include "GameFramework/PlayerState.h"
#include "EngineUtils.h"

void AHeistPVEGameState::PostInitializeComponents()
{
    UWorld *CurrentWorld = GetWorld();

    Super::PostInitializeComponents();

    if(CurrentWorld != nullptr)
    {
        for(TActorIterator<APlayerState>itr(CurrentWorld); itr; ++itr)
        {
            AddPlayerState(*itr);
        }
    }
}