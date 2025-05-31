// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Test_TaskHUD.generated.h"

class UAttributesWidget;
/**
 *
 */
UCLASS()
class TEST_TASK_API ATest_TaskHUD : public AHUD
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void RemoveAttributeWidget();

	bool IsWidgetVisible() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributesWidget> AttributeWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UAttributesWidget> AttributeWidget;
};
