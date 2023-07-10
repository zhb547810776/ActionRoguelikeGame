// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZRedBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZRedBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZRedBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY()
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh_Barrel;

	UFUNCTION()
	void RedBarrelExplode( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
