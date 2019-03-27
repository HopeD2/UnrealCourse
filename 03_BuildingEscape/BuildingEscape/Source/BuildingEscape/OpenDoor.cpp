// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	m_hasDoorOpened = false;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_hasDoorOpened) {
		FRotator rotator = GetOwner()->GetActorRotation();
		UE_LOG(LogTemp, Warning, TEXT("Current Yaw is : %f"), rotator.Yaw);
		rotator.Yaw -= 90;
		UE_LOG(LogTemp, Warning, TEXT("Current Yaw is : %f"), rotator.Yaw);
		GetOwner()->SetActorRotation(rotator);
		m_hasDoorOpened = true;
	}
}

