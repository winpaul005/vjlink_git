// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SceneCaptureComponent2D.h>
#include "Kismet/KismetRenderingLibrary.h"
#include "C_CCTVCam.generated.h"
//Literally a CCTV Cam which does absolutely nothing, what else do you except it to do, run at you with full speed and mutilate you while you're still alive?
UCLASS()
class VJLINK_API AC_CCTVCam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_CCTVCam();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneCaptureComponent2D* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
