// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZProjectile.h"
#include "ZBlackHoleProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKEGAME_API AZBlackHoleProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	AZBlackHoleProjectile();
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;
	
	virtual void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
