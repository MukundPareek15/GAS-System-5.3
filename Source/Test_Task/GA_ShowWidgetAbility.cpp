// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ShowWidgetAbility.h"
#include "AttributesWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"


void UGA_ShowWidgetAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	// TODO: logic to show widget + apply GE
	if (IsValid(WidgetClass))
	{
		AbilityWidget = Cast<UAttributesWidget>(CreateWidget(GetWorld(), WidgetClass));

		if (AbilityWidget != nullptr)
		{
			AbilityWidget->AddToViewport();
		}
	}
}

void UGA_ShowWidgetAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	// TODO: remove widget + remove GE
	if (AbilityWidget)
	{
		AbilityWidget->RemoveFromParent();
		AbilityWidget = nullptr;
	}
}