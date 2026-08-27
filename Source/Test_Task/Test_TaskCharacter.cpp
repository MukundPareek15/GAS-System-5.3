// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test_TaskCharacter.h"
#include "Test_TaskProjectile.h"
#include "InteractiveWidget.h"
#include "Blueprint/UserWidget.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TaskAbilitySystemComponent.h"
#include "Test_TaskPlayerState.h"
#include "Test_TaskHUD.h"
#include "AbilitySystemComponent.h"
#include "TaskAttributeSet.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATest_TaskCharacter

ATest_TaskCharacter::ATest_TaskCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

UAbilitySystemComponent* ATest_TaskCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UTaskAttributeSet* ATest_TaskCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ATest_TaskCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	InitDefaultAttributes();
	//InitHUD();
}

void ATest_TaskCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
}

//////////////////////////////////////////////////////////////////////////// Input

void ATest_TaskCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATest_TaskCharacter::OnBeginOverlap);

	if (IsValid(WidgetClass))
	{
		TextWidget = CreateWidget<UInteractiveWidget>(GetWorld(), WidgetClass);

		if (TextWidget != nullptr)
		{
			TextWidget->AddToViewport();
		}
	}
}

void ATest_TaskCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATest_TaskCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATest_TaskCharacter::Look);

		// ActivateAbility
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Started, this, &ATest_TaskCharacter::StartShowingHUDAndDamaging);
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Completed, this, &ATest_TaskCharacter::StopShowingHUDAndDamaging);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATest_TaskCharacter::InitHUD() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ATest_TaskHUD* TestHUD = Cast<ATest_TaskHUD>(PlayerController->GetHUD()))
		{
			TestHUD->Init();
		}
	}
}


void ATest_TaskCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() && IsValid(OtherActor) && OtherActor->ActorHasTag("Damage"))
	{
		ApplyHealthChange(-10.0f);
		UE_LOG(LogTemp, Warning, TEXT("Overlapped! Health: %f"), GetCurrentHealth());
	}
}

void ATest_TaskCharacter::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);
	if (!HasAuthority())
	{
		return;
	}

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		if (AbilityClass)
		{
			const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void ATest_TaskCharacter::InitAbilitySystemComponent()
{
	ATest_TaskPlayerState* TestPlayerState = GetPlayerState<ATest_TaskPlayerState>();
	check(TestPlayerState);
	AbilitySystemComponent = CastChecked<UTaskAbilitySystemComponent>
		(
			TestPlayerState->GetAbilitySystemComponent()
		);
	AbilitySystemComponent->InitAbilityActorInfo(TestPlayerState, this);
	AttributeSet = TestPlayerState->GetAttributeSet();
}

void ATest_TaskCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATest_TaskCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATest_TaskCharacter::InitDefaultAttributes() const
{
	if (!HasAuthority() || !AbilitySystemComponent || !DefaultAttributeEffect)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void ATest_TaskCharacter::ApplyHealthTick()
{
	ApplyHealthChange(-1.0f);

	if (TextWidget && GetCurrentHealth() <= 0.0f)
	{
		TextWidget->Dead();
	}
}

void ATest_TaskCharacter::ApplyHealthChange(float Delta)
{
	if (!HasAuthority() || !AbilitySystemComponent || !AttributeSet)
	{
		return;
	}

	const float NewHealth = FMath::Clamp(GetCurrentHealth() + Delta, 0.0f, GetMaximumHealth());
	AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), NewHealth);

	if (TextWidget)
	{
		TextWidget->UpdateHealthBar(NewHealth, GetMaximumHealth());
	}
}

float ATest_TaskCharacter::GetCurrentHealth() const
{
	return AttributeSet ? AttributeSet->GetHealth() : 0.0f;
}

float ATest_TaskCharacter::GetMaximumHealth() const
{
	return AttributeSet ? AttributeSet->GetMaxHealth() : 0.0f;
}

void ATest_TaskCharacter::StartShowingHUDAndDamaging()
{
	InitHUD();

	// Start applying health damage every second
	GetWorld()->GetTimerManager().SetTimer(HealthReductionTimer, this, &ATest_TaskCharacter::ApplyHealthTick, 1.0f, true);

	if (TextWidget)
	{
		TextWidget->UpdateHealthBar(GetCurrentHealth(), GetMaximumHealth());
	}
}

void ATest_TaskCharacter::StopShowingHUDAndDamaging()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ATest_TaskHUD* TestHUD = Cast<ATest_TaskHUD>(PlayerController->GetHUD()))
		{
			TestHUD->RemoveAttributeWidget();
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(HealthReductionTimer);
}
