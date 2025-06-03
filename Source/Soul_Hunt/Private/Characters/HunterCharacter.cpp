// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HunterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Chaos/SoftsSpring.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"GroomComponent.h"

// Sets default values
AHunterCharacter::AHunterCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate= FRotator(0.0f,400.f,0.0f);
	
	SpringArm= CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm-> TargetArmLength = 300.f;

	
	//JumpMaxHoldTime = 0.2f;
	GetCharacterMovement()->JumpZVelocity = 420.f;
	GetCharacterMovement()->AirControl = 0.35f;
	//GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("ViewCamera");
	ViewCamera->SetupAttachment(SpringArm);


	Hair= CreateDefaultSubobject<UGroomComponent>("Hair");
	Hair-> SetupAttachment(GetMesh());
	Hair-> AttachmentName= FString("head");


	Eyebrows= CreateDefaultSubobject<UGroomComponent>("Eyebrows");
	Eyebrows-> SetupAttachment(GetMesh());
	Eyebrows-> AttachmentName= FString("head");
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
	
	PlayerInputComponent->BindAction(FName("Jump"),IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&AHunterCharacter::StartRunning);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&AHunterCharacter::StopRunning);
	
}

void AHunterCharacter::MoveForward(float Value)
{
	if (Controller && (Value!=0.f))
	{
		/*FVector Forward= GetActorForwardVector();
		AddMovementInput(Forward, Value);*/

		//find out which way is forward

		const FRotator ControlRotation= GetControlRotation();
		const FRotator YawRotation(0.f,ControlRotation.Yaw,0.f);

		const FVector Direction= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,Value);
		
	}
}

void AHunterCharacter::MoveRight(float Value)
{
	if (Controller && (Value!=0.f))
	{
		/*FVector Right= GetActorRightVector();
		AddMovementInput(Right, Value);*/

		//find out which way is right
		const FRotator ControlRotation= GetControlRotation();
		const FRotator YawRotation(0.f,ControlRotation.Yaw,0.f);

		const FVector Direction= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction,Value);
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


/*void AHunterCharacter::Jump(float Value)
{
	
}*/

void AHunterCharacter::StartRunning()
{
	bIsRunning=true;
	GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
}

void AHunterCharacter::StopRunning()
{
	bIsRunning=false;
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
}

void AHunterCharacter::SetCharacterState(ECharacterState NewState)
{
	CharacterState = NewState;

}




