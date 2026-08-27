// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "Test_TaskCharacter.generated.h"

class UInputComponent;
class UPrimitiveComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UGameplayAbility;
class UTaskAbilitySystemComponent;
class UTaskAttributeSet;
class UGameplayEffect;
class UInteractiveWidget;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class ATest_TaskCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AbilityAction;

public:
	ATest_TaskCharacter();

	// ~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~End IAbilitySystemInterface interface
	virtual UTaskAttributeSet* GetAttributeSet() const;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Ability|Attributes")
	void ApplyHealthChange(float Delta);

	UFUNCTION(BlueprintPure, Category = "Ability|Attributes")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintPure, Category = "Ability|Attributes")
	float GetMaximumHealth() const;

protected:

	void GiveDefaultAbilities();
	void InitAbilitySystemComponent();
	void InitDefaultAttributes() const;

	UPROPERTY(EditAnywhere, Category = "HUD Class")
	TSubclassOf<UInteractiveWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TObjectPtr<UInteractiveWidget> TextWidget;

	UPROPERTY()
	TObjectPtr<UTaskAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTaskAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	FTimerHandle HealthReductionTimer;

	UFUNCTION()
	void StartShowingHUDAndDamaging();

	UFUNCTION()
	void StopShowingHUDAndDamaging();

	UFUNCTION()
	void ApplyHealthTick();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	UFUNCTION(BlueprintCallable)
	void InitHUD() const;

};

