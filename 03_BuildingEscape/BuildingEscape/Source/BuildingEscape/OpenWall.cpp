// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenWall.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UOpenWall::UOpenWall()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenWall::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* actor : FoundActors)
	{
		if (actor->GetName().Contains("Room3_Lamp")) {
			WallLamps.push_back(actor);
		}
	}

	/*for (AActor* Lamp : WallLamps)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor : %s"),*Lamp->GetName());
	}*/

	Owner = GetOwner();
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No Owner found!"));
	}
}


// Called every frame
void UOpenWall::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool AreAllLampsInCorrectPosition = false;

	for (size_t i = 0; i < WallLamps.size(); i++)
	{
		if ((int)WallLamps[i]->GetActorRotation().Roll == 0) {
			AreAllLampsInCorrectPosition = true;
		}
		else {
			AreAllLampsInCorrectPosition = false;
			break;
		}
	}

	if (AreAllLampsInCorrectPosition) {
		if (!HasWallOpened) {
			FRotator WallRotation = Owner->GetActorRotation();
			WallRotation.Pitch += -90;
			Owner->SetActorRotation(WallRotation);
			HasWallOpened = true;
		}
	}
}

