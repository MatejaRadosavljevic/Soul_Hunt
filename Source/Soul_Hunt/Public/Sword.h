// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"


class UBoxComponent;
class USphereComponent;
class UStaticMeshComponent;
class USceneComponent;
//class USoundBase;
class UGeometryCollectionComponent;


UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering    UMETA(DisplayName = "Hovering"),
	EIS_Equipped    UMETA(DisplayName = "Equipped"),
	EIS_Max         UMETA(DisplayName = "DefaultMAX")
};


UCLASS()
class SOUL_HUNT_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();
	
	virtual void Tick(float DeltaTime) override;

	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	//void DeactivateEmbers();
	void DisableSphereCollision();
	//void PlayEquipSound();
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item State")
	EItemState ItemState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SwordMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;

	UPROPERTY(EditAnywhere, Category = "Trace")
	FVector BoxTraceExtent = FVector(5.f);

	UPROPERTY(EditAnywhere, Category = "Trace")
	bool bShowBoxDebug = false;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 20.f;


	TArray<AActor*> IgnoreActors;

	UFUNCTION()																	
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void BoxTrace(FHitResult& BoxHit);

	void ExecuteHit(FHitResult& HitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
	
	
};
