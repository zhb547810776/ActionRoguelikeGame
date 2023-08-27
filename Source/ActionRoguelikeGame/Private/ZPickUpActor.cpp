// Fill out your copyright notice in the Description page of Project Settings.


#include "ZPickUpActor.h"

// Sets default values
AZPickUpActor::AZPickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;

}

// Called when the game starts or when spawned
void AZPickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZPickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZPickUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!AffectPawn(InstigatorPawn))
	{
		return;
	}
	
	if(bUseOnce)
	{
		Destroy();
	}
	else
	{
		if(HiddenTime > 0)
		{
			StaticMeshComp->SetHiddenInGame(true);
			SetActorEnableCollision(false);
			GetWorldTimerManager().SetTimer(TimerHandle_InteractionHidden, this, &AZPickUpActor::ShowSelf_TimeElapsed, HiddenTime);
		}
	}
}

void AZPickUpActor::ShowSelf_TimeElapsed()
{
	SetActorEnableCollision(true);
	StaticMeshComp->SetHiddenInGame(false);
}

bool AZPickUpActor::AffectPawn(APawn* InstigatorPawn)
{
	return false;
}
