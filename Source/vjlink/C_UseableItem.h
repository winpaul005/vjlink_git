// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom Events")
		FString EventId;
	UPROPERTY(BlueprintAssignable, Category = "Custom Events")
	FOnUseItem OnUseItem;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
