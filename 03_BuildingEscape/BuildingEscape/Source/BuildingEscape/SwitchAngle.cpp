// Fill out your copyright notice in the Description page of Project Settings.

#include "SwitchAngle.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values for this component's properties
USwitchAngle::USwitchAngle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitchAngle::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	GetInputComponent();
	
}


// Called every frame
void USwitchAngle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);*/
}

void USwitchAngle::GetInputComponent()
{
	InputComponent = Owner->FindComponentByClass<UInputComponent>();

	if (InputComponent){
		InputComponent->BindAction("Rotate", IE_Pressed, this, &USwitchAngle::RotateStaticMeshObject);
	}
	else {

	}
}

FVector USwitchAngle::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Gets player ViewPoint as a vector and rotation object
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Resultant vector of player location and where you are actually looking.
	return PlayerViewPointRotation.Vector() * Reach + PlayerViewPointLocation;
}

FVector USwitchAngle::GetReachLineStart()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation,
		PlayerRotation);

	return PlayerLocation;
}

void USwitchAngle::RotateStaticMeshObject()
{


	UE_LOG(LogTemp, Warning, TEXT("RotateStaticMeshObject !!"));
	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),  // Type of Object Channel required.
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())  // Additional behavior for collision params, eg: last param says what to ignore
	);

	if (HasHit) {
		UE_LOG(LogTemp, Warning, TEXT("Has Hit !!"));
		FRotator HitActorRotation = HitResult.Actor->GetActorRotation();
		HitActorRotation.Roll += 30.0f;
		HitResult.Actor->SetActorRotation(HitActorRotation);
	}
}

