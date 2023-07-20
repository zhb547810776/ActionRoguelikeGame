// Fill out your copyright notice in the Description page of Project Settings.


#include "ZMagicProjectile.h"
// #include "Components/SphereComponent.h"
// #include "Particles/ParticleSystemComponent.h"
// #include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AZMagicProjectile::AZMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	// //SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	// //SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// //SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	// //SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	// SphereComp->SetCollisionProfileName("Projectile");
	// RootComponent = SphereComp;
	//
	// EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	// EffectComp->SetupAttachment(SphereComp);
	//
	// MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	// MovementComp->InitialSpeed = 1000.f;
	// MovementComp->bRotationFollowsVelocity = true;
	// MovementComp->bInitialVelocityInLocalSpace = true;
	// MovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AZMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

