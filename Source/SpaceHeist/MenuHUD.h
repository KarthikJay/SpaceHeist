// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 *
 */
UCLASS(config=Game)
class SPACEHEIST_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	void ShowMenu();
	void RemoveMenu();
	void ShowServerMenu();

protected:

	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;
	TSharedPtr<class SServerMenuWidget> ServerMenuWidget;
	TSharedPtr<class SWidget> ServerMenuWidgetContainer;

	virtual void BeginPlay() override;
};
