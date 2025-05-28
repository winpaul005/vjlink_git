// Fill out your copyright notice in the Description page of Project Settings.


#include "C_FuncLadder.h"
#include "Components/BoxComponent.h"
// Sets default values
AC_FuncLadder::AC_FuncLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LadderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ladder Mesh"));
	BorderBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BorderBox->SetupAttachment(LadderMesh);
	BorderBox->OnComponentBeginOverlap.AddDynamic(this, &AC_FuncLadder::Overlap);
	BorderBox->OnComponentEndOverlap.AddDynamic(this, &AC_FuncLadder::EndOverlap);
	bIsFirstTime = true;
}

void AC_FuncLadder::Overlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GrabbedCharacter = Cast<AC_PlayerCharacter>(OtherActor);
	if (GrabbedCharacter)
	{
		if (!GrabbedCharacter->GetCharacterMovement()->IsFalling())
		{
			if (!bIsFirstTime)
			{
				GrabbedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
				GrabbedCharacter->bIsClimbing = false;
			}
		}
		else
		{
			bIsFirstTime = false;
		}
		GrabbedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		GrabbedCharacter->bIsClimbing = true;
	}

}

void AC_FuncLadder::EndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GrabbedCharacter = Cast<AC_PlayerCharacter>(OtherActor);
	if (GrabbedCharacter)
	{
		if (!bIsFirstTime)
		{
			bIsFirstTime = true;
		}
		GrabbedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		GrabbedCharacter->bIsClimbing = false;
	}
}

// Called when the game starts or when spawned
void AC_FuncLadder::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AC_FuncLadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

