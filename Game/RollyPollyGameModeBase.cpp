// Fill out your copyright notice in the Description page of Project Settings.


#include "RollyPollyGameModeBase.h"
#include "RollyPollyWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RollyPolly/Items/RollyPollyItemBase.h"

void ARollyPollyGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollyPollyItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass)
	{
		GameWidget = Cast<URollyPollyWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollyPollyGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollyPollyGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
