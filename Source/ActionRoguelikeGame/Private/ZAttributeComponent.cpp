// Fill out your copyright notice in the Description page of Project Settings.


#include "ZAttributeComponent.h"

bool UZAttributeComponent::IsAlive() const
{
	return Health > 0;
}

// Sets default values for this component's properties
UZAttributeComponent::UZAttributeComponent()
{
	Health = HealthMax;
}

bool UZAttributeComponent::ApplyHealthChange(float ChangedHealth)
{
	//float NewHealth = Health + ChangedHealth;
	Health += ChangedHealth;

	Health = FMath::Clamp(Health, 0.f, HealthMax);

	OnHealthChanged.Broadcast(nullptr, this, Health, ChangedHealth);
	
	return true;
}