// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "SServerMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "SpaceHeistGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    ShowMenu();

}
void AMenuHUD::ShowMenu()
{
    if(GEngine && GEngine->GameViewport)
    {
        MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

        if(PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());

        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = false;
            PlayerOwner->SetInputMode(FInputModeGameOnly());

            Cast<USpaceHeistGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->HostSession(GEngine->GetFirstGamePlayer(GetWorld())->GetPreferredUniqueNetId().GetUniqueNetId(), FName(TEXT("TestSession")), true, 5);
        }
    }
}

void AMenuHUD::ShowServerMenu()
{
    if (GEngine && GEngine->GameViewport)
    {
        ServerMenuWidget = SNew(SServerMenuWidget).OwningHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(ServerMenuWidgetContainer, SWeakWidget).PossiblyNullContent(ServerMenuWidget.ToSharedRef()));

        if(PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
}