// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesWidget.h"
#include "AbilitySystemComponent.h"
#include "TaskAttributeSet.h"
#include "Test_TaskPlayerState.h"

void UAttributesWidget::BindToAttributes()
{
	UnbindFromAttributes();

	const ATest_TaskPlayerState* TaskPlayerState = Cast<ATest_TaskPlayerState>(GetOwningPlayerState());
	if (!TaskPlayerState)
	{
		return;
	}

	BoundAbilitySystemComponent = TaskPlayerState->GetAbilitySystemComponent();
	BoundAttributeSet = TaskPlayerState->GetAttributeSet();
	if (!BoundAbilitySystemComponent || !BoundAttributeSet)
	{
		return;
	}

	RefreshHealthPercent();

	HealthChangedDelegateHandle = BoundAbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(BoundAttributeSet->GetHealthAttribute())
		.AddUObject(this, &UAttributesWidget::HandleAttributeChanged);

	MaxHealthChangedDelegateHandle = BoundAbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(BoundAttributeSet->GetMaxHealthAttribute())
		.AddUObject(this, &UAttributesWidget::HandleAttributeChanged);
}

void UAttributesWidget::NativeDestruct()
{
	UnbindFromAttributes();
	Super::NativeDestruct();
}

void UAttributesWidget::HandleAttributeChanged(const FOnAttributeChangeData&)
{
	RefreshHealthPercent();
}

void UAttributesWidget::RefreshHealthPercent()
{
	if (!BoundAttributeSet)
	{
		HealthPercent = 0.0f;
		return;
	}

	const float MaxHealth = BoundAttributeSet->GetMaxHealth();
	HealthPercent = MaxHealth > 0.0f
		? FMath::Clamp(BoundAttributeSet->GetHealth() / MaxHealth, 0.0f, 1.0f)
		: 0.0f;
}

void UAttributesWidget::UnbindFromAttributes()
{
	if (BoundAbilitySystemComponent && BoundAttributeSet)
	{
		if (HealthChangedDelegateHandle.IsValid())
		{
			BoundAbilitySystemComponent
				->GetGameplayAttributeValueChangeDelegate(BoundAttributeSet->GetHealthAttribute())
				.Remove(HealthChangedDelegateHandle);
		}

		if (MaxHealthChangedDelegateHandle.IsValid())
		{
			BoundAbilitySystemComponent
				->GetGameplayAttributeValueChangeDelegate(BoundAttributeSet->GetMaxHealthAttribute())
				.Remove(MaxHealthChangedDelegateHandle);
		}
	}

	HealthChangedDelegateHandle.Reset();
	MaxHealthChangedDelegateHandle.Reset();
	BoundAbilitySystemComponent = nullptr;
	BoundAttributeSet = nullptr;
}
