// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_CCTVCam.h"
#include "C_CCTVCenter.generated.h"
// CCTV Center which basically switches Texture outputs from cameras by placing a single RenderTarget2D texture to Texture Output of a chosen cam. 
// NOTE: do not forget
UCLASS()
class VJLINK_API AC_CCTVCenter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_CCTVCenter();
	TArray<AC_CCTVCam*> bindedCCTVCams;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int activeCam = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
