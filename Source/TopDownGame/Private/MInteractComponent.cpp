// Fill out your copyright notice in the Description page of Project Settings.


#include "MInteractComponent.h"
#include "MGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMInteractComponent::UMInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMInteractComponent::BasicInteract()
{	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	
	FVector OwnerLocation = MyOwner->GetActorLocation();
	TArray<FHitResult> Hits;
	float Radius = 40.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits, OwnerLocation, OwnerLocation, FQuat::Identity, ObjectQueryParams, Shape);
	
	FColor ColorLine = bBlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<UMGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IMGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, ColorLine, false, 2.f);
	}

	
}

