// Fill out your copyright notice in the Description page of Project Settings.

#include "SMainMenuWidget.h"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
    bCanSupportFocus = true;
    
    OwningHUD = InArgs._OwningHUD;

    const FMargin ContentPadding = FMargin(500.f, 300.f); //The most obvious margins to make the buttons and title not span the entire screen
    const FMargin ButtonPadding = FMargin(10.f); //provides margins buttons such that buttons don't touch each other

    const FText TitleText = LOCTEXT("GameTitle", "Space Heist");
    const FText CreateSessionText = LOCTEXT("Create Session", "Create Session");
    const FText SettingsText = LOCTEXT("Settings", "Settings");
    const FText FindSessionsText = LOCTEXT("Find Sessions", "Find Sessions");
    const FText QuitText = LOCTEXT("QuitGame", "Quit Game");

    FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
    ButtonTextStyle.Size = 40.f;

    FSlateFontInfo TitleTextStyle = ButtonTextStyle;
    TitleTextStyle.Size = 60.f;

    ChildSlot
        [
            SNew(SOverlay)
            + SOverlay::Slot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            [
                SNew(SImage)
                .ColorAndOpacity(FColor::Black) //Sets background to be black
            ]
            + SOverlay::Slot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .Padding(ContentPadding)
            [
                SNew(SVerticalBox)

                //Title Text
                + SVerticalBox::Slot()
                [
                    SNew(STextBlock)
                    .Font(TitleTextStyle)
                    .Text(TitleText)
                    .Justification(ETextJustify::Center)

                ]

                //Create Session Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    .OnClicked(this, &SMainMenuWidget::OnCreateSessionClicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(CreateSessionText)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]    

                //Find Sessions Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    .OnClicked(this, &SMainMenuWidget::OnFindSessionsClicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(FindSessionsText)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]

                //Settings Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(SettingsText)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]

                //Quit Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    .OnClicked(this, &SMainMenuWidget::OnQuitClicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(QuitText)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]

            ]
        ];
}

FReply SMainMenuWidget::OnCreateSessionClicked() const 
{
    UE_LOG(LogTemp,Warning, TEXT("Create Session Button Clicked"));
    if (OwningHUD.IsValid())
    {
        OwningHUD->RemoveMenu(); //this to be replaced with Tang's networking code
    }
    
    return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const 
{
    UE_LOG(LogTemp,Warning, TEXT("Quit Button Clicked"));
    if(OwningHUD.IsValid())
    {
        if(APlayerController* PC = OwningHUD->PlayerOwner)
        {
            PC->ConsoleCommand("quit");
        }
    }

    return FReply::Handled();
}

FReply SMainMenuWidget::OnFindSessionsClicked() const 
{
    UE_LOG(LogTemp,Warning, TEXT("Find Sessions Button Clicked"));
    if (OwningHUD.IsValid())
    {
        OwningHUD->RemoveMenu();
        OwningHUD->ShowServerMenu();
    }
    
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE


