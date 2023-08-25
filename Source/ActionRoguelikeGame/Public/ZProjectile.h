// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class UAudioComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ExplosionComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComp_Loop;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComp_Impact;

	UFUNCTION(BlueprintCallable)
	virtual void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ProjectileDamage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
