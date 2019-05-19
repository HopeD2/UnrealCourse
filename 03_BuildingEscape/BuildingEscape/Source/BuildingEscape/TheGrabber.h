// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "TheGrabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UTheGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTheGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Reach in cms to know how far we can reach
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;
	
	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	UInputComponent *InputComponent = nullptr;
	
	//Line trace and grab an object
	void Grab();

	//Release a grabbed object
	void Release();

	//Get attached Physics Handle
	void FindPhysicsHandleComponent();

	//Get attached Input component
	void GetInputComponent();

	//Return hit for first physics body in reach
	bool GetFirstPhysicsBodyInReach(FHitResult &HitResult);

	//Calculate Line Trace End based on players location and viewpoint direction
	FVector GetReachLineEnd();

	FVector GetReachLineStart();
};
