// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Objects/FinishLine.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	
	PrimaryActorTick.bCanEverTick = false;


	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(100.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);

	// Učitaj referencu na widget blueprint iz Content foldera
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/UI_Finished.UI_Finished"));
	if (WidgetClass.Succeeded())
	{
		FinishScreenClass = WidgetClass.Class;
	}
}


// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFinishLine::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		// Odloži prikaz UI-a za 0.3s
		GetWorld()->GetTimerManager().SetTimer(FinishTimerHandle, this, &AFinishLine::ShowFinishScreen, 0.3f, false);
	}
}

void AFinishLine::ShowFinishScreen()
{
	// Pauziraj igru
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// Prikazi UI
	if (FinishScreenClass)
	{
		UUserWidget* FinishWidget = CreateWidget<UUserWidget>(GetWorld(), FinishScreenClass);
		if (FinishWidget)
		{
			FinishWidget->AddToViewport();
		}
	}
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

