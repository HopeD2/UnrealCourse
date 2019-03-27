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
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor)) 
	{
		OpenDoor();
	}
	else {
		CloseDoor();
	}

}

void UOpenDoor::OpenDoor()
{
	if (!HasDoorOpened) {
		FRotator rotator = GetOwner()->GetActorRotation();
		UE_LOG(LogTemp, Warning, TEXT("Current Yaw is : %f"), rotator.Yaw);
		rotator.Yaw -= 90;
		UE_LOG(LogTemp, Warning, TEXT("Current Yaw is : %f"), rotator.Yaw);
		GetOwner()->SetActorRotation(rotator);
		HasDoorOpened = true;
	}
}

void UOpenDoor::CloseDoor()
{
	if (HasDoorOpened)
	{
		FRotator rotator = GetOwner()->GetActorRotation();
		UE_LOG(LogTemp, Warning, TEXT("Current Yaw is : %f"), rotator.Yaw);
		rotator.Yaw += 90;
		UE_LOG(LogTemp, Warning, TEXT("Current Yaw is : %f"), rotator.Yaw);
		GetOwner()->SetActorRotation(rotator);
		HasDoorOpened = false;
	}
}


