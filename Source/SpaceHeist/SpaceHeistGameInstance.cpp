#include "SpaceHeistGameInstance.h"
#include "Kismet/GameplayStatics.h"


USpaceHeistGameInstance::USpaceHeistGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	IOnlineSessionPtr Sessions = IOnlineSubsystem::Get()->GetSessionInterface();
	/** Bind function for creating a Session */
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &USpaceHeistGameInstance::OnCreateSessionComplete);
	//OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &USpaceHeistGameInstance::OnStartOnlineGameComplete);

}

bool USpaceHeistGameInstance::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsPresence, uint32 MaxNumPlayers)
{
	// Get the SessionInterface to work with
	IOnlineSessionPtr Sessions = IOnlineSubsystem::Get()->GetSessionInterface();
	if (Sessions.IsValid())
	{
		FOnlineSessionSettings SessionSettings;

		// TODO: Check errors for SessionInterface!
		// SessionSettings = MakeShareable<FOnlineSessionSettings>(new FOnlineSessionSettings());
		SessionSettings.bUsesPresence = bIsPresence;
		SessionSettings.NumPublicConnections = MaxNumPlayers;
		SessionSettings.bAllowInvites = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinViaPresence = true;

		SessionSettings.Set(SETTING_MAPNAME, FString("NewMap"), EOnlineDataAdvertisementType::ViaOnlineService);

		/*
		// TODO: FIX THIS! Causes CTD with access violation error thrown!
		if (!OnCreateSessionCompleteDelegateHandle.IsValid())
			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
		else
		{
			OnCreateSessionCompleteDelegateHandle.Reset();
			UE_LOG(LogTemp, Warning, TEXT("Got Here!"));
			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			UE_LOG(LogTemp, Warning, TEXT("Got Here 2!"));
		}
		*/


		OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

		// Our delegate should get called when this is complete (doesn't need to be successful!)
		return Sessions->CreateSession(*UserId, SessionName, SessionSettings);
	}
	else
		return false;
}

void USpaceHeistGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	// Get the SessionInterface to work with
	IOnlineSessionPtr Sessions = IOnlineSubsystem::Get()->GetSessionInterface();

	// Clear the SessionComplete delegate handle, since we finished this call
	Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
	if (bWasSuccessful)
	{
		// Set the StartSession delegate handle
		OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
		// Our StartSessionComplete delegate should get called after this
		Sessions->StartSession(SessionName);
	}

}

void USpaceHeistGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSessionPtr Sessions = IOnlineSubsystem::Get()->GetSessionInterface();
	UE_LOG(LogTemp, Warning, TEXT("OnStartOnlineGameComplete was called!"));


	if (Sessions.IsValid())
	{
		// Clear the delegate, since we are done with this call
		Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		OnStartSessionCompleteDelegateHandle.Reset();
	}

	// If the start was successful, we can open a NewMap if we want. Make sure to use "listen" as a parameter!
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("About to call OpenLevel!"));
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap", true, "listen");
	}
}
