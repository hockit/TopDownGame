// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttributeComponent.h"

// Sets default values for this component's properties
UMAttributeComponent::UMAttributeComponent()
{
	Health = 100.f;
}

bool UMAttributeComponent::HealthChange(float Delta)
{
	Health += Delta;

	return true;
}


