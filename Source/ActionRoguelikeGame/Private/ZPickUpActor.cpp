// Fill out your copyright notice in the Description page of Project Settings.


#include "AZPickUpActor.h"

// Sets default values
AZPickUpActor::AZDroppedPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	AZPickUpActor.bCanEverTick = true;

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

