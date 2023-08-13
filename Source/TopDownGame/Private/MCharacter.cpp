// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

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

	FireSound = CreateDefaultSubobject<USoundCue>("FireSound");
}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &AMCharacter::StopFire);
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

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation, 3.f);
	GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParams);
}




void AMCharacter::StopFire()
{
	
}