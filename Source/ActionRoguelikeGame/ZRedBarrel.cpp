// Fill out your copyright notice in the Description page of Project Settings.


#include "ZRedBarrel.h"

#include "PhysXPublic.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AZRedBarrel::AZRedBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetStaticMesh(StaticMesh_Barrel);
	
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AZRedBarrel::RedBarrelExplode);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->Radius = 700;
	RadialForceComp->ImpulseStrength = 2000;
	RadialForceComp->bImpulseVelChange = true;

}

// Called when the game starts or when spawned
void AZRedBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZRedBarrel::RedBarrelExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	RadialForceComp->FireImpulse();
}

// Called every frame
void AZRedBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

