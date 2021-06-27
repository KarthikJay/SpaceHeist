#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HeistPlayerState.generated.h"

/**
 *
 */
UCLASS(config=Game)
class SPACEHEIST_API AHeistPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	virtual void OverrideWith(class APlayerState* PlayerState) override;


protected:
	/** Can be negative to represent debt */
	UPROPERTY()
	int64 Money;

};
