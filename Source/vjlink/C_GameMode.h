// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_PlayerCharacter.h"
#include "C_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class VJLINK_API AC_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AC_GameMode();
	void PauseGame(bool bIsPaused);
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bSelectMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CacheInventoryItemID;
	FInventoryItem BufferItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText CacheText;
	UFUNCTION(BlueprintCallable)
	void AssignBuffer(FInventoryItem InputItem);
};
