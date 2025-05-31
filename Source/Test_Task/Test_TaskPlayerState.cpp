// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_TaskPlayerState.h"
#include "TaskAbilitySystemComponent.h"
#include "TaskAttributeSet.h"

ATest_TaskPlayerState::ATest_TaskPlayerState()
{
	NetUpdateFrequency = 100.f;

	// Create Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UTaskAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UTaskAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ATest_TaskPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UTaskAttributeSet* ATest_TaskPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
