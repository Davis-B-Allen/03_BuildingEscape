// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_03_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


private:
    // How far away the player can reach in cm
	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UInputComponent* InputComponent = nullptr;

	// Raycast and grab what's in reach
	void Grab();

	// Release currently grabbed object
	void Release();

	// Find attached physics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Get endpoint of player's grab reach
	FVector GetReachLineEnd();

	// Get startpoint of player's grab reach, which is the the same as the player's viewpoint location
	FVector GetReachLineStart();
};
