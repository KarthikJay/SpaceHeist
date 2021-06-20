// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SServerMenuWidget : public SCompoundWidget
{
public:

SLATE_BEGIN_ARGS(SServerMenuWidget) {}

SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)

SLATE_END_ARGS()

/** every widget needs a construction function */
void Construct(const FArguments& InArgs);

FReply OnServer_1Clicked() const;
FReply OnServer_2Clicked() const;
FReply OnBackClicked() const;

/**The HUD that created this widget*/
TWeakObjectPtr<class AMenuHUD> OwningHUD;

virtual bool SupportsKeyboardFocus() const override { return true; };

};
