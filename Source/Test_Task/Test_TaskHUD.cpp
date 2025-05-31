// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_TaskHUD.h"
#include "AttributesWidget.h"


void ATest_TaskHUD::Init()
{
	//if (!AttributeWidget && AttributeWidgetClass)
	//{
	AttributeWidget = CreateWidget<UAttributesWidget>(GetOwningPlayerController(), AttributeWidgetClass);
	//if (AttributeWidget)
	//{
	AttributeWidget->BindToAttributes();
	AttributeWidget->AddToViewport();
	//}
//}
/*if (AttributeWidgetClass)
{
	AttributesWidget = CreateWidget<UAttributesWidget>(GetWorld(), AttributeWidgetClass);
	if (AttributesWidget)
	{
		AttributesWidget->AddToViewport();
		AttributesWidget->BindToAttributes();
	}
}*/
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
