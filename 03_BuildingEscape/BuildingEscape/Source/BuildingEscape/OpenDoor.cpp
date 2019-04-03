// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HasDoorOpened = false;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No Owner found!"));
	}

	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("PressurePlate is empty, No Trigger Volume Assigned!"));
		return;
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPressurePlate() > TriggerMass) 
	{
		OpenDoor();
	}
	else 
	{
		CloseDoor();
	}

}

void UOpenDoor::OpenDoor()
{
	if (!HasDoorOpened) {

		if (Owner == nullptr) return;
		//Owner->SetActorRotation(FRotator(0.0f,-OpenDoorAngle,0.0f));
		OnOpen.Broadcast();
		HasDoorOpened = true;
	}
}

void UOpenDoor::CloseDoor()
{
	if (HasDoorOpened)
	{
		if (Owner == nullptr) return;
		OnClose.Broadcast();
		HasDoorOpened = false;
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0.0f;

	///Get All actors overlapping the pressure plate(trigger Volume) and store them in a TArray
	TArray<AActor*> OverlappingActors;
	if (PressurePlate == nullptr) { return 0; }
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}


