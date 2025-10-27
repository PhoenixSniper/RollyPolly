// Fill out your copyright notice in the Description page of Project Settings.


#include "RollyPollyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RollyPolly/Items/RollyPollyItemBase.h"

void ARollyPollyGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollyPollyItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();
}

void ARollyPollyGameModeBase::UpdateItemText()
{
}

void ARollyPollyGameModeBase::ItemCollected()
{
	ItemsCollected++;
}
