// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameMode.h"
#include "Kismet/GameplayStatics.h"

AC_GameMode::AC_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	bSelectMode = false;
	CacheInventoryItemID = -1;
	
}
void AC_GameMode::PauseGame(bool bIsPaused)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Paused"));
	UGameplayStatics::SetGamePaused(this, bIsPaused);

}

void AC_GameMode::AssignBuffer(FInventoryItem InputItem)
{
	BufferItem = InputItem;
}

void AC_GameMode::RefreshSeed()
{
	if (Seed == NULL)
	{
		RandomStream.GenerateNewSeed();
		Seed = RandomStream.GetCurrentSeed();

	}
}
