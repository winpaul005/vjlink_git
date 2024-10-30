// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "C_JukeBox.generated.h"

UCLASS()
class VJLINK_API AC_JukeBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_JukeBox();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* JukeboxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cues")
	TArray<USoundBase*> JukeboxCues;
	UFUNCTION(BlueprintCallable)
	void PlayCue(int cueIndex, bool IsImmediate);
	UFUNCTION(BlueprintCallable)
	void StopAll();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
