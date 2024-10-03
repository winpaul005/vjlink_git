// Fill out your copyright notice in the Description page of Project Settings.
#include "C_InventoryComponent.h"

#include "C_PlayerCharacter.h"



// Sets default values for this component's properties
UC_InventoryComponent::UC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InvnentorySize = 6;

	// ...
}


// Called when the game starts
void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UC_InventoryComponent::AddToInventory(FString ItemID)
{
	if (ItemsTable.DataTable != nullptr)
	{
		if (InventoryArray.Num() < InvnentorySize)
		{
			auto FoundRow = ItemsTable.DataTable->FindRow<FInventoryItem>(FName(*ItemID), "", true);
			if (FoundRow != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item Found: %s"), *FoundRow->ItemName);
				InventoryArray.Add(FInventorySlot());
				InventoryArray.Last().ItemID = ItemID;
				UE_LOG(LogTemp, Warning, TEXT("Availible slots left: %s"), *FString::FromInt(InvnentorySize - InventoryArray.Num()));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Item Not Found in the Table: %s"), *ItemID);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is full"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable not found"));
	}
	
}

void UC_InventoryComponent::RemoveFromInventory(FInventoryItem InputItem)
{
	
}

