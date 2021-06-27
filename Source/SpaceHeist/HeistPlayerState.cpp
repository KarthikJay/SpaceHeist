#include "HeistPlayerState.h"
#include "GameFramework/GameStateBase.h"


void AHeistPlayerState::CopyProperties(class APlayerState* PlayerState)
{
    Super::CopyProperties(PlayerState);
    AHeistPlayerState *CurrentPS = CastChecked<AHeistPlayerState>(PlayerState);
}

void AHeistPlayerState::OverrideWith(class APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
    AHeistPlayerState *CurrentPS = CastChecked<AHeistPlayerState>(PlayerState);
}
