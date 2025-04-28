// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerCharacter.h"
#include "C_GameMode.h"
#include "C_UseableItem.h"
#include "Kismet/GameplayStatics.h"
#include "C_InventoryComponent.h"
#include "DrawDebugHelpers.h"


//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
//FUCK AI ART
AC_PlayerCharacter::AC_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ChatterboxComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Chatterbox Component"));
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 85.0f);
	GetCapsuleComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	bUseControllerRotationRoll = false;
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(RootComponent);
	MainCamera->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	MainCamera->bUsePawnControlRotation = true;
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(MainCamera);
	SpotLight -> SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	InventoryComponent = CreateDefaultSubobject<UC_InventoryComponent>(TEXT("Inventory"));
	Health = 100.0f;
	ChargeFlashlight = 1.0f;
	bIsInventoryOpen = false;
	bIsFlashlightActive = false;
	bCanLook = true;
	bOutOfOrder = false;
	bIsReading = false;
	TotalPagesLeft = 0;
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	holdingWeight = 0.0f;
	bIsHolding = false;
	curDist = 185.0f;
	
}



void AC_PlayerCharacter::AddCharge(float Charge)
{
	if (ChargeFlashlight + Charge > 1.0f)
	{
		ChargeFlashlight = 1.0f;
	}
	else
	{
		ChargeFlashlight += Charge;
	}
}

void AC_PlayerCharacter::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AC_PlayerCharacter::OnEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
void AC_PlayerCharacter::Punch(float Damage)
{
	if (bOutOfOrder != true)
	{
		if (Health - Damage > 0.0f)
		{
			Health -= Damage;

		}
		else {
			Health = 0.0f;
			OnDeadEvent.Broadcast();
			bOutOfOrder = true;
		}
	}
}
void AC_PlayerCharacter::Heal(float Health_add)
{
	if (Health + Health_add < 100.0f)
	{
		Health += Health_add;
	}
	else
	{
		Health = 100.0f;
	}
}
// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//------------INPUT SETUP -------------------------------------------------------------
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AC_PlayerCharacter::OnEndOverlap);
	//-----------------------------------------------------------------------------------
	if (Player_Widget_Class != nullptr)
	{
		Player_Widget = CreateWidget(GetWorld(), Player_Widget_Class);
		Player_Widget->AddToViewport();
	}
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	MyController->SetInputMode(FInputModeGameOnly());
	WidgetInitCompleted.Broadcast();

}

void AC_PlayerCharacter::Move(const FInputActionValue& Value)
{
	if (bOutOfOrder != true && bCanLook ==true) {
		FVector2D MovementVector = Value.Get<FVector2D>();
		if (Controller != nullptr)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector XDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector YDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			//NOTE: For some reason XDirection and YDirection are f***d up, doing what they're supposed to do vice versa.
			//Keep that in mind.
			//NOTE: Formula for movement: (Y vector * Speed *(1 - (mass / 8)))
			AddMovementInput(XDirection, (MovementVector.Y * 0.6f) * (1 - (holdingWeight/500)));
			AddMovementInput(YDirection, (MovementVector.X * 0.6f) * (1 - (holdingWeight /500)));

		}
	}
}


void AC_PlayerCharacter::Use()
{
	if (bOutOfOrder != true)
	{
		//Ruling out we accidentally use item while reading
		if (bIsReading) {

			Unread();

		}
		else
		{
			if (bIsWatchingAtUseable)
			{
				UE_LOG(LogTemp, Warning, TEXT("Useable Item: %s"), *WatchableItem->GetName());
				Cast<AC_UseableItem>(WatchableItem)->UseItem(Cast<AC_GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CacheInventoryItemID);

			}
			Cast<AC_GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CacheInventoryItemID = -1;
		}

	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), GetWorld()->GetFName());
	}
}

	void AC_PlayerCharacter::Flashlight()
	{
		//wUE_LOG(LogTemp, Warning, TEXT("Charge left: %s"), (ChargeFlashlight * 100.0f));

		if(bOutOfOrder != true)
		{
			if (ChargeFlashlight > 0.0f)
			{
				if (bIsFlashlightActive)
				{
					bIsFlashlightActive = false;
				}
				else
				{
					bIsFlashlightActive = true;
				}
			}

		}

	}

void AC_PlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && bCanLook==true)
	{
		AddControllerYawInput((LookAxisVector.Y) * (1 - (holdingWeight / 500)));
		AddControllerPitchInput((LookAxisVector.X) * (powf(1 - (holdingWeight / 500),2)));
	}	
}

void AC_PlayerCharacter::Discard()
{
	Cast<AC_GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CacheInventoryItemID = -1;
}

void AC_PlayerCharacter::Quit()
{
	UE_LOG(LogTemp, Warning, TEXT("Is Paused%s "), bPaused ? TEXT("True") : TEXT("False"));
	if (bPaused)
	{
		bPaused = false;
		FGenericPlatformMisc::RequestExit(false);
	}
}

void AC_PlayerCharacter::Pause()
{
	if(bOutOfOrder !=true)
	{
		if (!bIsInventoryOpen)
		{
			if (!bPaused)
			{
				bPaused = true;
			}
			else
			{
				bPaused = false;
			}
			GetWorld()->GetAuthGameMode<AC_GameMode>()->PauseGame(bPaused);
		}
	}
}

void AC_PlayerCharacter::Grab()
{
	FVector StartLine = MainCamera->GetComponentLocation();
	FVector ForwardLine = MainCamera->GetForwardVector();
	FVector End = ((ForwardLine * 185.0f) + StartLine);
	FHitResult outRes;
	FCollisionQueryParams CollisionParams;
	FCollisionObjectQueryParams ObjectCollisionParams;
	ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	UE_LOG(LogTemp, Warning, TEXT("Triggered!"));
	if(bIsHolding)
	{
		PhysicsHandle->ReleaseComponent();
		bIsHolding = false;
		holdingWeight = 0.0f;
		curDist = 185.0f;
	}
	else
	{
		
		if (GetWorld()->LineTraceSingleByObjectType(outRes,StartLine,End, ObjectCollisionParams,CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				
				PhysicsHandle->SetTargetLocation(OutHit.ImpactPoint);
				PhysicsHandle->GrabComponentAtLocation(OutHit.GetComponent(), NAME_None, OutHit.ImpactPoint);
				curDist = OutHit.Distance;
				//500 kg = Cannot move, just tug
				if (!(PhysicsHandle->GetGrabbedComponent()->GetMass() >= 500.0f))
				{
					UE_LOG(LogTemp, Warning, TEXT("Grabbed!"));
					holdingWeight = PhysicsHandle->GetGrabbedComponent()->GetMass();
					bIsHolding = true;
				}
				else 
				{
					PhysicsHandle->ReleaseComponent();
					bIsHolding = false;
					holdingWeight = 0.0f;
					curDist = 185.0f;
				}


			}
		}
	}
}

void AC_PlayerCharacter::OpenInventory()
{	if(bOutOfOrder !=true)
	{
		if (!bIsReading)
		{
			APlayerController* MyController = GetWorld()->GetFirstPlayerController();
			Freeze(bIsInventoryOpen, MyController, true);
		}
		else
		{

			Unread();
		}
	}
}
void AC_PlayerCharacter::Knife()
{
	FVector StartLine = MainCamera->GetComponentLocation();
	FVector ForwardLine = MainCamera->GetForwardVector();
	FVector End = ((ForwardLine * 185.0f) + StartLine);
	FCollisionQueryParams CollisionParams;
	UGameplayStatics::PlaySound2D(GetWorld(), WhooshSound);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLine, End, ECC_Visibility, CollisionParams))
	{
		
		if (IsValid(OutHit.GetActor()))
		{
			if (OutHit.GetActor()->IsA(AC_UseableItem::StaticClass()))
			{
				Cast<AC_UseableItem>(OutHit.GetActor())->HitMe();
			}
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, OutHit.GetActor()->GetActorLabel());
			FRotator rott = OutHit.Normal.Rotation()+ FRotator(90.0f,0.f,0.f);
			ADecalActor* hitDecalActor = GetWorld()->SpawnActor<ADecalActor>(OutHit.ImpactPoint, rott);
			if (hitDecalActor)
			{
				hitDecalActor->SetDecalMaterial(KnifeDecal);
				hitDecalActor->SetLifeSpan(2.0f);
				hitDecalActor->SetActorScale3D(FVector(.05f, .05f, .001f));
			}
			UGameplayStatics::PlaySound2D(GetWorld(), ClingSound);
		}
	}
}
void AC_PlayerCharacter::Read(FText TextToRead)
{
	Cast<AC_GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CacheText = TextToRead;
	UE_LOG(LogTemp, Warning, TEXT("Read: %s"), *TextToRead.ToString());
	OnReadEvent.Broadcast();
	Freeze(bIsReading, GetWorld()->GetFirstPlayerController(),false);
	bIsReading = true;

}
void AC_PlayerCharacter::Unread()
{
		Freeze(bIsReading, GetWorld()->GetFirstPlayerController(), false);
		bIsReading = false;
}
void AC_PlayerCharacter::Freeze(bool &bReferenceBoolean, APlayerController* MyController, bool bEnableMouse)
{
	if (!bReferenceBoolean)
	{
		if (bEnableMouse)
		{
			MyController->bShowMouseCursor = true;
			MyController->bEnableClickEvents = true;
			MyController->bEnableMouseOverEvents = true;
			MyController->SetInputMode(FInputModeGameAndUI());
		}
		bCanLook = false;
		bReferenceBoolean = true;
	}
	else
	{
		if(bEnableMouse)
		{
			MyController->bShowMouseCursor = false;
			MyController->bEnableClickEvents = false;
			MyController->bEnableMouseOverEvents = false;
			MyController->SetInputMode(FInputModeGameOnly());
		}
		bCanLook = true;
		bReferenceBoolean = false;
	}
}
// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector StartLine = MainCamera->GetComponentLocation();
	FVector ForwardLine = MainCamera->GetForwardVector();
	FVector End = ((ForwardLine * 244.0f) + StartLine);
	FCollisionQueryParams CollisionParams;
//	DrawDebugLine(GetWorld(), StartLine, End, FColor::Green, false, 1, 0, 1);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLine, End, ECC_Visibility, CollisionParams))
	{
		if (IsValid(OutHit.GetActor()) && OutHit.GetActor()->IsA(AC_UseableItem::StaticClass()))
		{
			if (Cast<AC_UseableItem>(OutHit.GetActor())->bIsBreakeable == false)
			{
				bIsWatchingAtUseable = true;
				WatchableItem = OutHit.GetActor();
			}
			else {
				bIsWatchingAtUseable = false;
				WatchableItem = nullptr;
			}
		}
		else 
		{
			bIsWatchingAtUseable = false;
			WatchableItem = nullptr;
		}

	}
	else {
		bIsWatchingAtUseable = false;
		WatchableItem = nullptr;
	}

	if (bIsHolding)
	{
		PhysicsHandle->SetTargetLocation(MainCamera->GetComponentLocation() + MainCamera->GetForwardVector() * curDist);
	}
	//Check what actors are we looking at
	FVector EndLook = ((ForwardLine * 844.0f) + StartLine);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLine, EndLook, ECC_Visibility, CollisionParams))
	{
		if (IsValid(OutHit.GetActor()))
		{
			LookAtClass = OutHit.GetActor();
		}
		else {
			LookAtClass = nullptr;
		}
	}

	//-------------------------------
	if (!bIsFlashlightActive)
	{
		SpotLight->SetIntensity(0.0f);
		/*if (ChargeFlashlight < 1.0f)
		{
			ChargeFlashlight += 0.01f * DeltaTime;
		}
		*/
	}
	else
	{
		SpotLight->SetIntensity(3000.0f);
		if (ChargeFlashlight > 0.0f)
		{
			ChargeFlashlight -= 0.01f * DeltaTime;
		}
		else
		{
			bIsFlashlightActive = false;
		}
	}
}

// Called to bind functionality to input
void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Bind all the Input Actions (TBA)
		//EXAMPLE: EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//And yada yada yada
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Use);
		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Flashlight);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_PlayerCharacter::Look);
		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Quit);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Pause);
		EnhancedInputComponent->BindAction(DiscardAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Discard);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::OpenInventory);
		EnhancedInputComponent->BindAction(KnifeAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Knife);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Grab);

	}

}

