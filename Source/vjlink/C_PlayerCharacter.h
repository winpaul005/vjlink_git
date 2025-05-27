// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Camera/CameraComponent.h"
#include <Engine/DecalActor.h>
#include "C_PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetInitCompleted);
USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemDescription;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ItemClass;
};

class UC_InventoryComponent;

UCLASS()
class VJLINK_API AC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_PlayerCharacter();
	UPROPERTY(EditDefaultsOnly)
	UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmC;
	float curDist;
	float holdingWeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsClimbing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UAudioComponent* ChatterboxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* FootstepsCue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* WhooshSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* ClingSound;
	UPROPERTY(BlueprintAssignable, Category = "Custom Events")
	FOnDead OnDeadEvent;
	UPROPERTY(BlueprintAssignable, Category = "Custom Events")
	FOnRead OnReadEvent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* MainCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpotLightComponent *SpotLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
	bool bIsInventoryOpen;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	UC_InventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	AActor* WatchableItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	bool bCanLook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	int InventoryWidth = 4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	int InventoryLength = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EscapeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FlashlightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DiscardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* KnifeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weaponry, meta = (AllowPrivateAccess = "true"))
	UMaterial* KnifeDecal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChargeFlashlight;
	UFUNCTION(BlueprintCallable)
	void AddCharge(float Charge);
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void OpenInventory();
	UFUNCTION(BlueprintCallable)
	void Knife();
	UFUNCTION(BlueprintCallable)
	void Read(FText TextToRead);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Player_Widget_Class;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* Player_Widget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> InventoryArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsWatchingAtUseable;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsFlashlightActive;
	bool bOutOfOrder;
	void Unread();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TotalPagesLeft;
	UPROPERTY(BlueprintAssignable, Category = "Custom Events")

	FOnWidgetInitCompleted WidgetInitCompleted;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsReading;
	UFUNCTION(BlueprintCallable)
	void Freeze(UPARAM(ref)bool& bReferenceBoolean, APlayerController* MyController, bool bEnableMouse);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bPaused;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCrouched;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* LookAtClass;
	UFUNCTION(BlueprintCallable)
	void Punch(float Damage);
	UFUNCTION(BlueprintCallable)
	void Heal(float Health_add);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FHitResult OutHit;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Use();
	void Flashlight();
	void Look(const FInputActionValue& Value);
	void Discard();
	void Quit();
	void Pause();
	void Grab();
	void Crouch();
	void UnCrouch();
	FHitResult crouchHit;
	FCollisionObjectQueryParams crouchParams;
	FCollisionQueryParams crouchCollisionParams;

	bool bIsHolding;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};