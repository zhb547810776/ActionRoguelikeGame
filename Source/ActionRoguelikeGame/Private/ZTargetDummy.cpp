// Fill out your copyright notice in the Description page of Project Settings.


#include "ZTargetDummy.h"

#include "ZAttributeComponent.h"

// Sets default values
AZTargetDummy::AZTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UZAttributeComponent>("AttributeComp");
	//AttributeComp->SetUp  Can't SetUpComponent ,it's SceneComponent 's function

	AttributeComp->OnHealthChanged.AddDynamic(this, &AZTargetDummy::OnHealthChanged);

}

// Called when the game starts or when spawned
void AZTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZTargetDummy::OnHealthChanged(AActor* InstigatorActor, UZAttributeComponent* OwningComp, float NewHealth, float ChangedHealth)
{
	if(ChangedHealth < 0 && NewHealth - ChangedHealth > 0)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	
}
