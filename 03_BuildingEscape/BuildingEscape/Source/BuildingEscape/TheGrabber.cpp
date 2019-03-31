// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGrabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Classes/Engine/World.h"

#define OUT

// Sets default values for this component's properties
UTheGrabber::UTheGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTheGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Get Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) {

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Missing for %s"),*GetOwner()->GetName());
	}
}


// Called every frame
void UTheGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Gets player ViewPoint as a vector and rotation object
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("Player Location is : %s, Rotation is : %s"),
	//	*PlayerViewPointLocation.ToString(),
	//	*PlayerViewPointRotation.ToString()
	//);

	// Resultant vector of player location and where you are actually looking.
	FVector LineTraceEnd = PlayerViewPointRotation.Vector() * Reach + PlayerViewPointLocation;

	// Draw debug line for vector from PlayerViewPointLocation to LineTraceEnd
	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0,
		10.0f
	);

	// LineTrace to check if a collision with Physics body is occurring
	FHitResult HitResult;
	bool hasHit = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),  // Type of Object Channel required.
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())  // Additional behavior for collision params, eg: last param says what to ignore
	);

	if (hasHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit a %s"), *HitResult.GetActor()->GetName());
	}

}

