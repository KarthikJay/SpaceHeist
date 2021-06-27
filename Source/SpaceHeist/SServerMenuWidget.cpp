// Fill out your copyright notice in the Description page of Project Settings.

#include "SServerMenuWidget.h"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "ServerMenu"

void SServerMenuWidget::Construct(const FArguments& InArgs)
{
    bCanSupportFocus = true;
    
    OwningHUD = InArgs._OwningHUD;

    const FMargin ContentPadding = FMargin(500.f, 300.f); //The most obvious margins to make the buttons and title not span the entire screen
    const FMargin ButtonPadding = FMargin(10.f); //provides margins buttons such that buttons don't touch each other

    const FText TitleText = LOCTEXT("GameTitle", "Space Heist");
    const FText SessionsText = LOCTEXT("Sessions", "Sessions");
    const FText Server1Text = LOCTEXT("Server 1", "Server 1");
    const FText Server2Text = LOCTEXT("Server 2", "Server 2");
    const FText BackText = LOCTEXT("Back", "Back");

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

                //Sessions Text
                + SVerticalBox::Slot()
                [
                    SNew(STextBlock)
                    .Font(TitleTextStyle)
                    .Text(SessionsText)
                    .Justification(ETextJustify::Center)

                ]

                //Server 1 Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    //.OnClicked(this, &SServerMenuWidget::OnServer1Clicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(Server1Text)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]

                //Server 2 Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    //.OnClicked(this, &SServerMenuWidget::OnServer2Clicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(Server2Text)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]    

                //Back Button
                + SVerticalBox::Slot()
                .Padding(ButtonPadding)
                [
                    SNew(SButton)
                    .OnClicked(this, &SServerMenuWidget::OnServerBackClicked)
                    [
                        SNew(STextBlock)
                        .Font(ButtonTextStyle)
                        .Text(BackText)
                        .Justification(ETextJustify::Center)
                    ]                   
                ]

            ]
        ];
}

FReply SServerMenuWidget::OnServerBackClicked() const 
{
    UE_LOG(LogTemp,Warning, TEXT("Server Back Button Clicked"));
    if (OwningHUD.IsValid())
    {
        OwningHUD->RemoveServerMenu();
        OwningHUD->ShowMenu();
    }
    
    return FReply::Handled();
}