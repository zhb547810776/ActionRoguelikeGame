// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "ZPickUpActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZPickUpActor : public AActor, public IZGamePlayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	AZPickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	bool bUseOnce;

	UFUNCTION()
	virtual bool AffectPawn(APawn* InstigatorPawn);

	FTimerHandle TimerHandle_InteractionHidden;

	UFUNCTION()
	virtual void ShowSelf_TimeElapsed();
	
	UPROPERTY(EditAnywhere)
	float HiddenTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
