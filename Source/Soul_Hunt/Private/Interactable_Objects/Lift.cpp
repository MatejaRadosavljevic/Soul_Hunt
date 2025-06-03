// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Objects/Lift.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"



// Sets default values
ALift::ALift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Lift mesh
	LiftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LiftMesh"));
	LiftMesh->SetupAttachment(RootComponent);

	// Trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ALift::BeginPlay()
{
	Super::BeginPlay();
	
	StartZ = GetActorLocation().Z;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALift::OnTriggerBegin);
}

void ALift::StartLift()
{
	bIsMoving = true;
}

// Called every frame
void ALift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		FVector Location = GetActorLocation();
		if (Location.Z < TargetZ)
		{
			Location.Z += LiftSpeed * DeltaTime;
			SetActorLocation(Location);
		}
		else
		{
			bIsMoving = false;
		}
	}

}

void ALift::OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (ACharacter* Player = Cast<ACharacter>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &ALift::StartLift, DelayBeforeMove, false);
	}
}

