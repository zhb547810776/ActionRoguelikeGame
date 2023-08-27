// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "ZDroppedPickUp.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZDroppedPickUp : public AActor, public IZGamePlayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	AZDroppedPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* StaticMeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
