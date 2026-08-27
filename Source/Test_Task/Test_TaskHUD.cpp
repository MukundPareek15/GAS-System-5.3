// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_TaskHUD.h"
#include "AttributesWidget.h"


void ATest_TaskHUD::Init()
{
	if (AttributeWidget && AttributeWidget->IsInViewport())
	{
		return;
	}

	if (!AttributeWidgetClass)
	{
		return;
	}

	AttributeWidget = CreateWidget<UAttributesWidget>(GetOwningPlayerController(), AttributeWidgetClass);
	if (!AttributeWidget)
	{
		return;
	}

	AttributeWidget->BindToAttributes();
	AttributeWidget->AddToViewport();
}

void ATest_TaskHUD::RemoveAttributeWidget()
{
	if (AttributeWidget)
	{
		AttributeWidget->RemoveFromParent();
		AttributeWidget = nullptr;
	}
}

bool ATest_TaskHUD::IsWidgetVisible() const
{
	return AttributeWidget && AttributeWidget->IsInViewport();
}
