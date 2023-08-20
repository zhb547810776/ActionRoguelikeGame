// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZTargetDummy.generated.h"

class UZAttributeComponent;
class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZTargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UZAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UZAttributeComponent* OwningComp, float NewHealth, float ChangedHealth);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
