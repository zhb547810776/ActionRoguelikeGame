// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZPickUpActor.h"
#include "ZHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKEGAME_API AZHealthPotion : public AZPickUpActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool AffectPawn(APawn* InstigatorPawn) override;

	UPROPERTY(EditAnywhere)
	float HealHealth;
	
};
