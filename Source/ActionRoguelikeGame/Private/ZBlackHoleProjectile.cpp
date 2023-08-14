// Fill out your copyright notice in the Description page of Project Settings.


#include "ZBlackHoleProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AZBlackHoleProjectile::AZBlackHoleProjectile() : AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Super::AProjectile();

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->Radius = 1000;
	RadialForceComp->ImpulseStrength = -4500;
	//RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bIgnoreOwningActor = true;
	RadialForceComp->RemoveObjectTypeToAffect(ObjectTypeQuery3);
	
	SphereComp->SetSphereRadius(50);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	//SphereComp->OnComponentBeginOverlap.RemoveAll(this);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AZBlackHoleProjectile::Explode_BlackHole);

	MovementComp->bSweepCollision = true;
}

// Called when the game starts or when spawned
void AZBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(5.0f);
}

// Called every frame
void AZBlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RadialForceComp->FireImpulse();
}

void AZBlackHoleProjectile::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::Explode(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetActorLabel());
	if(OtherActor != GetInstigator())
	{
		OtherActor->Destroy();
	}
	//Super::Explode(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}