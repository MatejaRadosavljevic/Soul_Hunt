// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HunterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Chaos/SoftsSpring.h"

// Sets default values
AHunterCharacter::AHunterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArm= CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm-> TargetArmLength = 300.f;
	JumpMaxHoldTime = 0.2f;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("ViewCamera");
	ViewCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AHunterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHunterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHunterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(FName("MoveForward"),this, &AHunterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"),this,&AHunterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"),this,&AHunterCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"),this,&AHunterCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("Jump"),this,&AHunterCharacter::Jump);
}

void AHunterCharacter::MoveForward(float Value)
{
	if (Controller && (Value!=0.f))
	{
		FVector Forward= GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

void AHunterCharacter::MoveRight(float Value)
{
	if (Controller && (Value!=0.f))
	{
		FVector Right= GetActorRightVector();
		AddMovementInput(Right, Value);
	}
}

void AHunterCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AHunterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AHunterCharacter::Jump(float Value)
{
	
}




