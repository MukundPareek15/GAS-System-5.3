// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ShowWidgetAbility.h"
#include "AttributesWidget.h"
#include "GameFramework/PlayerController.h"

UGA_ShowWidgetAbility::UGA_ShowWidgetAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}

void UGA_ShowWidgetAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!ActorInfo || !ActorInfo->IsLocallyControlled() || !CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	APlayerController* PlayerController = ActorInfo->PlayerController.Get();
	if (!PlayerController || !WidgetClass)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	AbilityWidget = CreateWidget<UAttributesWidget>(PlayerController, WidgetClass);
	if (!AbilityWidget)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	AbilityWidget->BindToAttributes();
	AbilityWidget->AddToViewport();
}

void UGA_ShowWidgetAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	if (AbilityWidget)
	{
		AbilityWidget->RemoveFromParent();
		AbilityWidget = nullptr;
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
