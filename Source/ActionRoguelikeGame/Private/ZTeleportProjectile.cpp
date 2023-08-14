// Fill out your copyright notice in the Description page of Project Settings.


#include "ZTeleportProjectile.h"

AZTeleportProjectile::AZTeleportProjectile()
{
	TeleportPlayerDelayTime = 0.5;
}

// Called when the game starts or when spawned
void AZTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TelepoetPlayerHandler, this, &AZTeleportProjectile::TeleportPlayer_TimeElapsed, TeleportPlayerDelayTime);
}

// Called every frame
void AZTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZTeleportProjectile::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GetInstigator() == OtherActor)
	{
		return;
	}
	
	Super::Explode(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	GetWorldTimerManager().ClearTimer(TelepoetPlayerHandler);
	//Teleport Player
	GetInstigator()->SetActorLocation(GetActorLocation());
}

void AZTeleportProjectile::TeleportPlayer_TimeElapsed()
{
	FHitResult Hit;
	
	Explode(nullptr, nullptr, nullptr, 0, false, Hit);
}
