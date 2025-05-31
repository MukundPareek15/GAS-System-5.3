// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributesWidget.generated.h"

class UProgressBar;
/**
 *
 */
UCLASS()
class TEST_TASK_API UAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToAttributes();

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPercent;


};
