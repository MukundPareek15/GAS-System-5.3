// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TaskAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
	AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)

/**
 *
 */
UCLASS()
class TEST_TASK_API UTaskAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UTaskAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTaskAttributeSet, Health)

		UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTaskAttributeSet, MaxHealth)

		UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;


};
