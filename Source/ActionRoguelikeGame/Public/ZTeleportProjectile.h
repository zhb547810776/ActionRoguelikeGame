// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZProjectile.h"
#include "ZTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKEGAME_API AZTeleportProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	AZTeleportProjectile();
	
protected:
	
	FTimerHandle TelepoetPlayerHandler;

	UPROPERTY(EditAnywhere)
	float TeleportPlayerDelayTime;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) __override;

	UFUNCTION()
	void TeleportPlayer_TimeElapsed();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
