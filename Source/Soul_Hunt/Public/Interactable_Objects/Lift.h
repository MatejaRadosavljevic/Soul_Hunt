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
	
	ALift();
	
protected:
	
	virtual void BeginPlay() override;

	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LiftMesh;

	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	// Target Z position
	UPROPERTY(EditAnywhere)
	float TargetZ = 500.f;

	// Delay before lift starts
	UPROPERTY(EditAnywhere)
	float DelayBeforeMove = 1.f;

	
	UPROPERTY(EditAnywhere)
	float LiftSpeed = 200.f;

	
	bool bIsMoving = false;

	
	UPROPERTY(BlueprintReadWrite)
	float StartZ;

	
	FTimerHandle DelayTimerHandle;

	
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
