// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY();
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemID;
};
class C_PlayerCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class VJLINK_API UC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_InventoryComponent();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle ItemsTable;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int InvnentorySize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FInventorySlot> InventoryArray;
	UFUNCTION(BlueprintCallable)
	void AddToInventory(FString ItemID);
	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(FInventoryItem InputItem);
};
