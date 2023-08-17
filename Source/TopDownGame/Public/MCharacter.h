// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UMAttributeComponent;
class UMInteractComponent;

UCLASS()
class TOPDOWNGAME_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UMInteractComponent* InteractComp;


	//FUNCTIONS

	void MoveForward(float Value);
	void MoveRight(float Value);

	void BasicInteract();

	void PrimaryAttack();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	
	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwnComp, float ChangedHealth, float Delta);
	virtual void PostInitializeComponents() override;

public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
