// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLine.generated.h"


class UBoxComponent;
class UUserWidget;

UCLASS()
class SOUL_HUNT_API AFinishLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishLine();

protected:
	
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> FinishScreenClass;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	FTimerHandle FinishTimerHandle;
	

	void ShowFinishScreen(); 
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
