// Fill out your copyright notice in the Description page of Project Settings.


#include "RollyPollyItemBase.h"

#include "RollyPolly/Game/RollyPollyGameModeBase.h"
#include "RollyPolly/Game/RollyPollyPlayer.h"

// Sets default values
ARollyPollyItemBase::ARollyPollyItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Components - Before this step they won't exist in our Actor, they've only been defined.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollyPollyItemBase::OverlapBegin);

}

// Called when the game starts or when spawned
void ARollyPollyItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ARollyPollyItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARollyPollyPlayer>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ARollyPollyItemBase::Collected_Implementation()
{
	ARollyPollyGameModeBase* GameMode = Cast<ARollyPollyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}


