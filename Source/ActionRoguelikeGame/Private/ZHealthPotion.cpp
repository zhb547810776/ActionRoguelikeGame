// Fill out your copyright notice in the Description page of Project Settings.


#include "ZHealthPotion.h"

#include "ZAttributeComponent.h"

void AZHealthPotion::BeginPlay()
{
	Super::BeginPlay();

	HealHealth = 20;
}

bool AZHealthPotion::AffectPawn(APawn* InstigatorPawn)
{
	if(InstigatorPawn)
	{
		UZAttributeComponent* AttributeComp = Cast<UZAttributeComponent>(InstigatorPawn->GetComponentByClass(UZAttributeComponent::StaticClass()));
		if(AttributeComp && !AttributeComp->IsFullHealth())
		{
			AttributeComp->ApplyHealthChange(HealHealth);
			return true;
		}
	}

	return false;
}
