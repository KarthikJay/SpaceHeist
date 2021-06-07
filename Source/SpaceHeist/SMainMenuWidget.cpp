// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{

    bCanSupportFocus = true;
    
    OwningHUD = InArgs._OwningHUD;

    const FMargin ContentPadding = FMargin(500.f, 300.f);
    const FMargin ButtonPadding = FMargin(10.f); //provides margins around buttons

    const FText TitleText = LOCTEXT("GameTitle", "Space Heist");
    const FText PlayText = LOCTEXT("PlayGame", "Play");
    const FText SettingsText = LOCTEXT("Settings", "Settings");
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

                //Play Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    .OnClicked(this, &SMainMenuWidget::OnPlayClicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(PlayText)
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

FReply SMainMenuWidget::OnPlayClicked() const 
{
    UE_LOG(LogTemp,Warning, TEXT("Play Button Clicked"));
    if (OwningHUD.IsValid())
    {
        OwningHUD->RemoveMenu();
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

#undef LOCTEXT_NAMESPACE


