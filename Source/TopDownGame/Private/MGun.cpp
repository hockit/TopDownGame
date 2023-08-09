// Fill out your copyright notice in the Description page of Project Settings.


#include "MGun.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMGun::AMGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = SceneComp;

	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalComp");
	SkeletalComp->SetupAttachment(SceneComp);
}

// Called when the game starts or when spawned
void AMGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMGun::SpawnProjectile()
{
	FVector MuzzleLocation = SkeletalComp->GetSocketLocation("MuzzleFlashSocket");

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FRotator MuzzleRotation = OwnerController->GetControlRotation();

	FTransform SpawnTM = FTransform(MuzzleRotation, MuzzleLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}