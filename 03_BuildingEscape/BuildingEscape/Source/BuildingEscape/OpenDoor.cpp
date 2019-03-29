// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HasDoorOpened = false;
	DoorLastOpenTime = 0.0f;
	OpenDoorAngle = 90.0f;
	DoorOpenDelayTime = 1.0f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor)) 
	{
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		float curTime = GetWorld()->GetTimeSeconds();
		if (curTime - DoorLastOpenTime > DoorOpenDelayTime) 
		{
			CloseDoor();
		}
	}

}

void UOpenDoor::OpenDoor()
{
	if (!HasDoorOpened) {
		Owner->SetActorRotation(FRotator(0.0f,-OpenDoorAngle,0.0f));
		HasDoorOpened = true;
	}
}

void UOpenDoor::CloseDoor()
{
	if (HasDoorOpened)
	{
		Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		HasDoorOpened = false;
	}
}


