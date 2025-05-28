// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlayerCharacter.h"
#include "C_UseableItem.h"
#include "C_FuncLadder.generated.h"

UCLASS()
class VJLINK_API AC_FuncLadder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_FuncLadder();
	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMeshComponent* LadderMesh;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UBoxComponent* BorderBox;
	bool bIsFirstTime;
	AC_PlayerCharacter* GrabbedCharacter;
	UFUNCTION()
	void Overlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
