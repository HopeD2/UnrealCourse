// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerCapsule.h"
#include <vector>
#include "OpenDoorBySequence.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorOpenSequenceEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorBySequence : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorBySequence();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();

	void CloseDoor();

	UPROPERTY(BlueprintAssignable)
		FDoorOpenSequenceEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorOpenSequenceEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleViolet = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleIndigo = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleBlue = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleGreen = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleYellow = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleOrange = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerCapsule *TriggerCapsuleRed = nullptr;

	ATriggerCapsule *TriggerCapsulePrevious = nullptr;

	std::vector<ATriggerCapsule*> TriggerColorCollection;

	bool currentTriggerCollection[7];

	bool HasDoorOpened = false;

	AActor* Owner = nullptr;

	AActor* ActorThatOpens = nullptr;
};
