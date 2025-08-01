// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "C_UseableItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUseItem, int,CacheInventoryItemId);
UCLASS()
class VJLINK_API AC_UseableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_UseableItem();
	UFUNCTION(BlueprintCallable, Category = "UseableItem")
		void UseItem(int CacheItemID);
	UFUNCTION(BlueprintCallable, Category = "UseableItem")
	void HitMe();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom Events")
		FString EventId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	bool bIsBreakeable;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	UMaterial* GlowMat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	int HitsLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* DestroySound;
	UPROPERTY(BlueprintAssignable, Category = "Custom Events")
	FOnUseItem OnUseItem;
	//bool bIsLookedAt;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
