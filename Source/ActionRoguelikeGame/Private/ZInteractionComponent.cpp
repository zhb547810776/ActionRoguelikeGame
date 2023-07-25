// Fill out your copyright notice in the Description page of Project Settings.


#include "ZInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "ZGamePlayInterface.h"

// Sets default values for this component's properties
UZInteractionComponent::UZInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UZInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UZInteractionComponent::PrimaryInteract()
{
	//FHitResult Hit;
	TArray<FHitResult> HitList;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FVector EyeLocation, EndLocation, ViewLocation, ViewDir;
	FRotator EyeRotation;

	AActor* ActorOwner = GetOwner();
	APlayerController* CurPC = Cast<APlayerController>(Cast<APawn>(ActorOwner)->Controller);

	if(CurPC != nullptr)
	{
		CurPC->DeprojectMousePositionToWorld(ViewLocation, ViewDir);
	}
	//ActorOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	//EndLocation = EyeLocation + EyeRotation.Vector() * 1000;
	EndLocation = ViewLocation + CurPC->GetControlRotation().Vector() * 1000;

	float SphereRaduis = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(SphereRaduis);
	
	//bool bCollideAnything = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EndLocation, ObjectQueryParams);
	//bool bCollideAnything = GetWorld()->SweepMultiByObjectType(HitList, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);
	bool bCollideAnything = GetWorld()->SweepMultiByObjectType(HitList, ViewLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bCollideAnything ? FColor::Green : FColor::Red;

	for (FHitResult Hit : HitList)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<UZGamePlayInterface>())
			{
				APawn* PawnOwner = Cast<APawn>(ActorOwner);
			
				IZGamePlayInterface::Execute_Interact(HitActor, PawnOwner);
				break;
			}
		}
	}
	

	DrawDebugLine(GetWorld(), ViewLocation, EndLocation, LineColor, false, 2.0f, 0 , 2.0f);
}
