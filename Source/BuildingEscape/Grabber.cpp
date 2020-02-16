// All Rights Reserved Leo Lee 2020

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Grabber.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void		UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputHandle();
}

// Called every frame
void		UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if physics handle is attached
		// move object we are holding
}

void		UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: PhysicsHandleComponent NOT found!"), *GetOwner()->GetName());
	}
	else
	{
		; // PhysicsHandle found!
	}
}

void		UGrabber::SetupInputHandle()
{
	// Check InputComponent
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: InputComponent NOT found!"), *GetOwner()->GetName());
	}
	else
	{
		InputHandle->BindAction("Interact", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Interact", IE_Released, this, &UGrabber::Release);
	}
}

void		UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

	// only raycast when key is pressed
	GetFirstPhysicsBodyInReach();
	// Try and reach any actors with phsyics body collision channel set

	// If we hit something, then attach the physics handle
	// TODO attach physics handle
}

void		UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));
}

FHitResult	UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector		PlayerViewPointLocation {};
	FRotator	PlayerViewPointDirection {};

	// Get Player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation,
		OUT	PlayerViewPointDirection
	);

	// Draw a line signifying player's POV
	FVector	LineTraceEnd {PlayerViewPointLocation + PlayerViewPointDirection.Vector() * Reach};

	// Ray-cast out to a certain distance
	FHitResult				Hit {};
	FCollisionQueryParams	TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// What are we hitting?
	if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.Actor->GetName());
	}
	else
	{
		;
	}

	// What are we hitting? Alternative approach
	// AActor					*ActorHit = Hit.GetActor();

	// if (ActorHit)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *(ActorHit->GetName())); 
	// }
	// else
	// {
	// 	;
	// }

	return Hit;
}
