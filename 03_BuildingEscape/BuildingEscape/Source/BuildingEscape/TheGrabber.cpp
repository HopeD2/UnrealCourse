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

	FindPhysicsHandleComponent();

	GetInputComponent();
}


// Called every frame
void UTheGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Resultant vector of player location and where you are actually looking.
	FVector LineTraceEnd = PlayerViewPointRotation.Vector() * Reach + PlayerViewPointLocation;

	//If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UTheGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	///Line Trace and see if we can reach any actors with physics body collision channel set
	FHitResult HitResult;
	bool HasHit = GetFirstPhysicsBodyInReach(HitResult);

	UPrimitiveComponent *ComponentToGrab = HitResult.GetComponent();

	// Attach physics handle only if we hit something
	if (HasHit) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			HitResult.Actor->GetActorLocation(),
			true //Allow rotation 
		);
	}

}

void UTheGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	PhysicsHandle->ReleaseComponent();
}

// Get attached Physics component Handle
void UTheGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Missing for %s"), *GetOwner()->GetName());
	}
}

// Get attached Input Component 
void UTheGrabber::GetInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("InputComponent Found"));

		InputComponent->BindAction("Grab", IE_Pressed, this, &UTheGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UTheGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent Missing for %s"), *GetOwner()->GetName());
	}
}

bool UTheGrabber::GetFirstPhysicsBodyInReach(FHitResult &HitResult)
{
	// Gets player ViewPoint as a vector and rotation object
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Resultant vector of player location and where you are actually looking.
	FVector LineTraceEnd = PlayerViewPointRotation.Vector() * Reach + PlayerViewPointLocation;

	// LineTrace to check if a collision with Physics body is occurring
	bool hasHit = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),  // Type of Object Channel required.
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())  // Additional behavior for collision params, eg: last param says what to ignore
	);

	return hasHit;
}

