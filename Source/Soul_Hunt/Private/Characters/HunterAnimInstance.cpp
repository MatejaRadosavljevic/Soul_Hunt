// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HunterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/HunterCharacter.h"

void UHunterAnimInstance::NativeInitializeAnimation()
{
	// Calling super because of overriding of a parent function
	Super::NativeInitializeAnimation();

	HunterCharacter= Cast<AHunterCharacter>(TryGetPawnOwner());
	if (HunterCharacter)
	{
		HunterCharacterMovement= HunterCharacter->GetCharacterMovement();
	}
	
}

void UHunterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	// Calling super because of overriding of a parent function
	Super::NativeUpdateAnimation(DeltaTime);

	if (HunterCharacterMovement)
	{
		
		GroundSpeed= UKismetMathLibrary::VSizeXY(HunterCharacterMovement->Velocity);
		IsFalling= HunterCharacterMovement->IsFalling();
		
	}
}
