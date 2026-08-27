#include "InteractiveWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Test_TaskCharacter.h"

void UInteractiveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ActionButton)
	{
		ActionButton->OnClicked.AddUniqueDynamic(this, &UInteractiveWidget::ActionButtonOnClicked);
	}
}

void UInteractiveWidget::NativeDestruct()
{
	if (ActionButton)
	{
		ActionButton->OnClicked.RemoveDynamic(this, &UInteractiveWidget::ActionButtonOnClicked);
	}

	Super::NativeDestruct();
}

void UInteractiveWidget::ActionButtonOnClicked()
{
	if (MessageLabel)
	{
		MessageLabel->SetText(FText::FromString("You are damaged!"));
	}

	ATest_TaskCharacter* MyChar = Cast<ATest_TaskCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyChar)
	{
		MyChar->ApplyHealthChange(-10.0f);
		UpdateHealthBar(MyChar->GetCurrentHealth(), MyChar->GetMaximumHealth());
	}
}

void UInteractiveWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		const float ClampedHealth = MaxHealth > 0.0f
			? FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f)
			: 0.0f;
		HealthBar->SetPercent(ClampedHealth);

		if (ClampedHealth <= 0.0f && MessageLabel)
		{
			Dead();
		}
		else if (MessageLabel)
		{
			MessageLabel->SetText(FText::FromString("You are damaged!"));
		}
	}

}

void UInteractiveWidget::Dead()
{
	if (MessageLabel)
	{
		MessageLabel->SetText(FText::FromString("You are dead!"));
	}
}
