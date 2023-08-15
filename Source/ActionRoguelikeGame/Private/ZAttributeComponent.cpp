// Fill out your copyright notice in the Description page of Project Settings.


#include "ZAttributeComponent.h"

// Sets default values for this component's properties
UZAttributeComponent::UZAttributeComponent()
{
	Health = 100;
}

bool UZAttributeComponent::ApplyHealthChange(float ChangedHealth)
{
	Health += ChangedHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, ChangedHealth);
	
	return true;
}