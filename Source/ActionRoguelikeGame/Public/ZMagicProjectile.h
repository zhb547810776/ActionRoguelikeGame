// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZProjectile.h"
#include "GameFramework/Actor.h"
#include "ZMagicProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZMagicProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZMagicProjectile();

protected:

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// USphereComponent* SphereComp;
	//
	// UPROPERTY(VisibleAnywhere)
	// UParticleSystemComponent* EffectComp;
	//
	// UPROPERTY(VisibleAnywhere)
	// UProjectileMovementComponent* MovementComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
