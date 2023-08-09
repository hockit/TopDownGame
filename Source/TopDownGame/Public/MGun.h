// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGun.generated.h"

class USceneComponent;
class USkeletalMeshComponent;

UCLASS()
class TOPDOWNGAME_API AMGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnProjectile();

};
