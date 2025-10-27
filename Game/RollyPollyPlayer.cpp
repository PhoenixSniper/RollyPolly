// Fill out your copyright notice in the Description page of Project Settings.


#include "RollyPollyPlayer.h"

#include "IDetailTreeNode.h"
#include "PropertyAccess.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "VerseVM/VBPVMRuntimeType.h"

// Sets default values
ARollyPollyPlayer::ARollyPollyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Create Components - Before this step they won't exist in our Actor, they've only been difined.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set the Root Component to be out Mesh.
	RootComponent = Mesh;
	// Attach the SpringArm to the Mesh, Spring will now follow the Mesh transform.
	SpringArm->SetupAttachment(Mesh);
	// Attach the Camera to the SpringArm, Camera will now follow the SpringArm transform.
	Camera->SetupAttachment(SpringArm);

	// Set physics to True
	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &ARollyPollyPlayer::OnHit);
	
}

// Called when the game starts or when spawned
void ARollyPollyPlayer::BeginPlay()
{
	Super::BeginPlay();
	// Account for mass in MoveForce
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
	
}

// Called to bind functionality to input
void ARollyPollyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Custom Input Axis Bindings.
	InputComponent->BindAxis("MoveForward", this, &ARollyPollyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this,  &ARollyPollyPlayer::MoveRight);
	// Custom Action Binding.
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollyPollyPlayer::Jump);

}

void ARollyPollyPlayer::MoveRight(float Value)
{
	// Get the Right Vector of the camera as it doesn't rotate and move the player in this direction based on the input and MoveForce.
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollyPollyPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollyPollyPlayer::Jump()
{
	// Cap the number of jumps we can make.
	if (JumpCount >= MaxJumpCount) { return; }
	// Apply an impulse to the Mesh in the Z Axis.
	Mesh->AddImpulse(FVector(0,0, JumpImpulse));
	JumpCount++;
}

void ARollyPollyPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Get Direction we hit the surface on the Z axis.
	const float HitDirection = Hit.Normal.Z;
	// If it's more than 0 then we've hit something below us. 1 is flat, anything between is a slope.
	if (HitDirection > 0)
	{
		JumpCount = 0;
	}
}

