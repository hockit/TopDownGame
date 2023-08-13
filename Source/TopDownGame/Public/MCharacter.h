// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundCue;

UCLASS()
class TOPDOWNGAME_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Fire")
	USoundCue* FireSound;

	bool bCanFire;

	//FUNCTIONS

	void MoveForward(float Value);
	void MoveRight(float Value);

	void PrimaryAttack();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	void StopFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
