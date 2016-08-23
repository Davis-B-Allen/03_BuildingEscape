

#include "Section_03.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

    Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
    // Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    // Set the door rotation
    Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume
    if (GetTotalMassOfActorsOnPlate() > 30.0f) // TODO make into a parameter
	{
		OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
    
    // Check to see if it's time to close the door
    if (GetWorld()->GetTimeSeconds() > LastDoorOpenTime+DoorCloseDelay)
    {
        CloseDoor();
    }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	// find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on Pressure Plate"), *Actor->GetName())
	}
	// iterate through them, adding their masses

	return TotalMass;
}