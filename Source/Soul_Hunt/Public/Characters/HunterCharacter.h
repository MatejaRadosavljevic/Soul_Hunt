// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "HunterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class UInputAction;




UCLASS()
class SOUL_HUNT_API AHunterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AHunterCharacter();
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
		// Called when the game starts or when spawned
    	virtual void BeginPlay() override;

		void MoveForward(float Value);

		void MoveRight(float Value);
	
		void Turn(float Value);
	
		void LookUp(float Value);
	
		//void Jump(float Value);

	/**Called for running input*/
	UFUNCTION()
	void StartRunning();

	UFUNCTION()
	void StopRunning();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State", meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState=ECharacterState::ECS_Unequipped;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;
	
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UFUNCTION(BlueprintCallable)
	void SetCharacterState(ECharacterState NewState);

	/** Running Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RunSpeed = 700.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 400.0f;

	bool bIsRunning = false;


	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;*/

	public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	
};
