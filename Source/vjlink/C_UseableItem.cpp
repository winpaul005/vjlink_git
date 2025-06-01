#include "C_UseableItem.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include <Kismet/GameplayStatics.h>

// Sets default values
AC_UseableItem::AC_UseableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Dump/MT_PickGlow.MT_PickGlow'"));

	//if (Material.Object != NULL)
	//{
		//GlowMat = (UMaterial*)Material.Object;
	//}
	//bIsLookedAt = false;
	HitsLeft = 5;

}

void AC_UseableItem::UseItem(int CacheItemID)
{
	//boo
	UE_LOG(LogTemp, Warning, TEXT("Useable Item used, %d"), CacheItemID);
	OnUseItem.Broadcast(CacheItemID);
}

void AC_UseableItem::HitMe()
{
	if(bIsBreakeable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hits Left %d"), HitsLeft);

		if (HitsLeft - 1 > 0)
		{
			HitsLeft -= 1;
		}
		else {
			UGameplayStatics::PlaySound2D(GetWorld(), DestroySound);
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AC_UseableItem::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AC_UseableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (bIsLookedAt)
	{
		this->FindComponentByClass<UStaticMeshComponent>()->SetOverlayMaterial(GlowMat);
	}
	else
	{
		this->FindComponentByClass<UStaticMeshComponent>()->SetOverlayMaterial(NULL);

	}*/
}

