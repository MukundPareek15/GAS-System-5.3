// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Test_Task.h"
#include "GA_ShowWidgetAbility.generated.h"

class UAttributesWidget;
/**
 *
 */
UCLASS()
class TEST_TASK_API UGA_ShowWidgetAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_ShowWidgetAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled) override;

	EAbilityInputID GetAbilityInputID() const { return AbilityInputID; }

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	EAbilityInputID AbilityInputID{ EAbilityInputID::None };

	UPROPERTY(EditAnywhere, Category = "HUD Class")
	TSubclassOf<UAttributesWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TObjectPtr<UAttributesWidget> AbilityWidget;

};
