// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveWidget.generated.h"


UCLASS(Abstract)
class TEST_TASK_API UInteractiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void Dead();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MessageLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ActionButton;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void ActionButtonOnClicked();

};
