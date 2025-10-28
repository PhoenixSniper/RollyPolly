// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollyPollyGameModeBase.generated.h"

class URollyPollyWidget;
/**
 * 
 */
UCLASS()
class ROLLYPOLLY_API ARollyPollyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollyPollyWidget* GameWidget;

	virtual void BeginPlay() override;

	void UpdateItemText();

public:

	void ItemCollected();
	
};
