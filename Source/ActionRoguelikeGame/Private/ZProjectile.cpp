// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\ZProjectile.h"

#include "ZAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::Explode);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	ExplosionComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplosiontComp");
	ExplosionComp->SetupAttachment(SphereComp);
	ExplosionComp->bAutoActivate = false;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == GetInstigator())
	{
		return;
	}

	if(OtherActor)
	{
		if(ProjectileDamage > 0)
		{
			UZAttributeComponent* AttributeComp = Cast<UZAttributeComponent>(OtherActor->GetComponentByClass(UZAttributeComponent::StaticClass()));
            if(AttributeComp)
            {
            	AttributeComp->ApplyHealthChange(-ProjectileDamage);
            }
		}

		if(ExplosionComp->Template != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetActorLabel());
			ExplosionComp->Activate();
			EffectComp->Deactivate();
			SetActorEnableCollision(false);
			MovementComp->StopMovementImmediately();
			InitialLifeSpan = 5.0f;
		}
	}
	
}
