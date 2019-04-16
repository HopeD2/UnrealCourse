// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorBySequence.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoorBySequence::UOpenDoorBySequence()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorBySequence::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No Owner found!"));
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ActorThatOpens == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No Pawn found!"));
	}

	if (TriggerCapsuleRed == nullptr || TriggerCapsuleOrange == nullptr || TriggerCapsuleYellow == nullptr || TriggerCapsuleGreen == nullptr
		|| TriggerCapsuleBlue == nullptr || TriggerCapsuleIndigo == nullptr || TriggerCapsuleViolet == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("One of the TriggerCapsule Handle is empty!"));
	}
	else {
		TriggerColorCollection.push_back(TriggerCapsuleViolet);
		TriggerColorCollection.push_back(TriggerCapsuleIndigo);
		TriggerColorCollection.push_back(TriggerCapsuleBlue);
		TriggerColorCollection.push_back(TriggerCapsuleGreen);
		TriggerColorCollection.push_back(TriggerCapsuleYellow);
		TriggerColorCollection.push_back(TriggerCapsuleOrange);
		TriggerColorCollection.push_back(TriggerCapsuleRed);
	}

	for (size_t i = 0; i < 7; i++)
	{
		currentTriggerCollection[i] = false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Vector size is : %d"),TriggerColorCollection.size());
	
}


// Called every frame
void UOpenDoorBySequence::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool IsSequenceComplete = false;

	int j = 0;

	if (TriggerCapsuleViolet->IsOverlappingActor(ActorThatOpens)  || currentTriggerCollection[0]) {
		currentTriggerCollection[j++] = true;
		if (TriggerCapsuleIndigo->IsOverlappingActor(ActorThatOpens) || currentTriggerCollection[1]) {
			currentTriggerCollection[j++] = true;
			if (TriggerCapsuleBlue->IsOverlappingActor(ActorThatOpens) || currentTriggerCollection[2]) {
				currentTriggerCollection[j++] = true;
				if (TriggerCapsuleGreen->IsOverlappingActor(ActorThatOpens) || currentTriggerCollection[3]) {
					currentTriggerCollection[j++] = true;
					if (TriggerCapsuleYellow->IsOverlappingActor(ActorThatOpens) || currentTriggerCollection[4]) {
						currentTriggerCollection[j++] = true;
						if (TriggerCapsuleOrange->IsOverlappingActor(ActorThatOpens) || currentTriggerCollection[5]) {
							currentTriggerCollection[j++] = true;
							if (TriggerCapsuleRed->IsOverlappingActor(ActorThatOpens) || currentTriggerCollection[6]) {
								currentTriggerCollection[j++] = true;
								IsSequenceComplete = true;
							}
						}
					}
				}
			}
		}
	}

	for (size_t i = 0; i < TriggerColorCollection.size(); i++)
	{
		if (i == j-1) {
			continue;
		}

		if (TriggerColorCollection[i]->IsOverlappingActor(ActorThatOpens)) {
			currentTriggerCollection[j-1] = false;
			IsSequenceComplete = false;
		}
	}

	for (size_t i = 0; i < TriggerColorCollection.size(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentTriggerCollection[%d] : %d"),i, currentTriggerCollection[i]);
	}

	if (IsSequenceComplete) {
		OpenDoor();
	}
	else {
		CloseDoor();
	}
	
}

void UOpenDoorBySequence::OpenDoor()
{
	if (!HasDoorOpened) {
		OnOpen.Broadcast();
		HasDoorOpened = true;
	}
}

void UOpenDoorBySequence::CloseDoor()
{
	if (HasDoorOpened) {
		OnClose.Broadcast();
		HasDoorOpened = false;
	}
}

