// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UTaskAttributeSet::UTaskAttributeSet()
{
	InitHealth(80.0f);
}

void UTaskAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTaskAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTaskAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UTaskAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxHealth());
	}
}

void UTaskAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp<float>(GetHealth(), 0.0f, GetMaxHealth()));
	}
	//// Example of how to get the instigator actor from the effect spec
	//UAbilitySystemComponent* ASC = Data.EffectSpec.GetContext().GetInstigatorAbilitySystemComponent();
	//AActor* ASCOwner = ASC->AbilityActorInfo->OwnerActor.Get();
	//ASCOwner->GetActorLocation();
}

void UTaskAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTaskAttributeSet, Health, OldHealth);
}

void UTaskAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTaskAttributeSet, MaxHealth, OldMaxHealth);
}
