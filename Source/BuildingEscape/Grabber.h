// All Rights Reserved Leo Lee 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void					Grab();
	void					Release();
	void					FindPhysicsHandle();
	void					SetupInputHandle();
	void					GetPlayerViewPoint();
	FHitResult				GetFirstPhysicsBodyInReach();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float					Reach {100.f};
	UPhysicsHandleComponent	*PhysicsHandle {nullptr};
	UInputComponent			*InputHandle {nullptr};
};
