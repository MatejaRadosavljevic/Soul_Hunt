// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lift.generated.h"

UCLASS()
class SOUL_HUNT_API ALift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALift();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Lift platform
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LiftMesh;

	// Trigger volume for activation
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	// Target Z position
	UPROPERTY(EditAnywhere)
	float TargetZ = 500.f;

	// Delay before lift starts
	UPROPERTY(EditAnywhere)
	float DelayBeforeMove = 1.f;

	// Speed of lift
	UPROPERTY(EditAnywhere)
	float LiftSpeed = 200.f;

	// Internal flag to check if it's moving
	bool bIsMoving = false;

	// Start Z
	UPROPERTY(BlueprintReadWrite)
	float StartZ;

	// Timer
	FTimerHandle DelayTimerHandle;

	// Function to start lift
	void StartLift();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Trigger overlap
	UFUNCTION()
	void OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

};
