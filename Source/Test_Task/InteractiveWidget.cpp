#include "InteractiveWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Test_TaskCharacter.h"

void UInteractiveWidget::NativeConstruct()
{
	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &UInteractiveWidget::ActionButtonOnClicked);
	}
}

void UInteractiveWidget::ActionButtonOnClicked()
{
	MessageLabel->SetText(FText::FromString("You are damaged!"));

	ATest_TaskCharacter* MyChar = Cast<ATest_TaskCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyChar)
	{
		MyChar->fPlayerHealth -= 10.0f; // Decrease health by 10
	}

	HealthBar->SetPercent((MyChar->fPlayerHealth) / 100);

	if (HealthBar->GetPercent() <= 0.0f)
	{
		Dead();
	}
}

void UInteractiveWidget::UpdateHealthBar(float CurrentHealth)
{
	if (HealthBar)
	{
		float ClampedHealth = FMath::Clamp(CurrentHealth / 100.0f, 0.0f, 1.0f);
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
	MessageLabel->SetText(FText::FromString("You are dead!"));
}
