// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Test_TaskPlayerState.generated.h"

class UTaskAbilitySystemComponent;
class UTaskAttributeSet;

UCLASS()
class TEST_TASK_API ATest_TaskPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATest_TaskPlayerState();

	// ~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~End IAbilitySystemInterface interface
	virtual UTaskAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY()
	TObjectPtr<UTaskAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTaskAttributeSet> AttributeSet;

};
