// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributesWidget.generated.h"

class UAbilitySystemComponent;
class UTaskAttributeSet;
struct FOnAttributeChangeData;
/**
 *
 */
UCLASS()
class TEST_TASK_API UAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindToAttributes();

protected:
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	float HealthPercent = 0.0f;

private:
	void HandleAttributeChanged(const FOnAttributeChangeData& Data);
	void RefreshHealthPercent();
	void UnbindFromAttributes();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> BoundAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTaskAttributeSet> BoundAttributeSet;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;

};
