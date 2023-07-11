// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "ZItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZItemChest : public AActor, public IZGamePlayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	AZItemChest();

protected:

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
