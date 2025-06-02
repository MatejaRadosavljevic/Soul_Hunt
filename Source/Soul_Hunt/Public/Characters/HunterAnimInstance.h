// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HunterCharacter.h"
#include "CharacterTypes.h"
#include "HunterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOUL_HUNT_API UHunterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AHunterCharacter* HunterCharacter;

	UPROPERTY(BlueprintReadOnly, Category= Movement)
	class UCharacterMovementComponent* HunterCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category= Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category= Movement)
	bool IsFalling;

	ECharacterState CharacterState;
	
};
