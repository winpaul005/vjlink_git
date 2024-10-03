// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CCTVCam.h"

// Sets default values
AC_CCTVCam::AC_CCTVCam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CCTV Camera"));


}

// Called when the game starts or when spawned
void AC_CCTVCam::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AC_CCTVCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

