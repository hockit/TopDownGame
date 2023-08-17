// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MAttributeComponent.h"
#include "MInteractComponent.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalComp");
	SkeletalComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket_01"));

	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");

	InteractComp = CreateDefaultSubobject<UMInteractComponent>("InteractComp");
}

void AMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChange.AddDynamic(this, &AMCharacter::OnHealthChange);
}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMCharacter::PrimaryAttack);
}

void AMCharacter::MoveForward(float Value)
{
	FRotator ControlRotation = GetControlRotation();

	AddMovementInput(ControlRotation.Vector(), Value);
}

void AMCharacter::MoveRight(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void AMCharacter::BasicInteract()
{
	if (InteractComp)
	{
		InteractComp->BasicInteract();
	}
}


void AMCharacter::PrimaryAttack()
{
	
	SpawnProjectile(ProjectileClass);
}

void AMCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	FVector MuzzleLocation = SkeletalComp->GetSocketLocation("MuzzleFlashSocket");

	FRotator MuzzleRotation = SkeletalComp->GetSocketRotation("MuzzleFlashSocket");

	FTransform SpawnTransform = FTransform(GetControlRotation(), MuzzleLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParams);
}

void AMCharacter::OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwnComp, float ChangedHealth, float Delta)
{
	if (ChangedHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
}