// Fill out your copyright notice in the Description page of Project Settings.


#include "C_JukeBox.h"

// Sets default values
AC_JukeBox::AC_JukeBox()
{
	JukeboxComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Jukebox Component"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AC_JukeBox::PlayCue(int cueIndex, bool IsImmediate)
{
	if ((!JukeboxComponent->IsPlaying() || (IsImmediate && JukeboxCues[cueIndex] != JukeboxComponent->GetSound())) && JukeboxCues[cueIndex] != nullptr)
	{
		JukeboxComponent->SetSound(JukeboxCues[cueIndex]);
		JukeboxComponent->Play();
	}
}

void AC_JukeBox::StopAll()
{
	JukeboxComponent->Stop();
}

// Called when the game starts or when spawned
void AC_JukeBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_JukeBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

