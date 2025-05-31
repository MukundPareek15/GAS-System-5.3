// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesWidget.h"
#include "TaskAttributeSet.h"
#include "Test_TaskPlayerState.h"

void UAttributesWidget::BindToAttributes()
{
	const ATest_TaskPlayerState* TaskPlayerState = Cast<ATest_TaskPlayerState>(GetOwningPlayerState());
	if (!TaskPlayerState) return;

	UAbilitySystemComponent* ASC = TaskPlayerState->GetAbilitySystemComponent();
	const UTaskAttributeSet* AttributeSet = TaskPlayerState->GetAttributeSet();

	//Initial Attributes
	HealthPercent = NUMERIC_VALUE(AttributeSet, Health) / NUMERIC_VALUE(AttributeSet, MaxHealth);

	//Bind to Attribute Changes
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddLambda(
		[this, AttributeSet](const FOnAttributeChangeData& Data)->void
		{
			HealthPercent = Data.NewValue / NUMERIC_VALUE(AttributeSet, MaxHealth);
		}
	);
}
