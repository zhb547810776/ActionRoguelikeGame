// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZCharacter.generated.h"

class UZAttributeComponent;
class USpringArmComponent;
class UCameraComponent;
class UZInteractionComponent;
class UAnimMontage;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKEGAME_API AZCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZCharacter();

protected:

	// UPROPERTY(VisibleAnywhere)
	// UParticleSystemComponent* ShootProjComp;
	UPROPERTY(EditAnywhere)
	UParticleSystem* ShootProjTemplate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category="Attack")
	float PrimaryAttackDelayTime;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	float BlackHoleAttackDelayTime;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> TeleportProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	float TeleportAttackDelayTime;
	
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_BlackHoleAttack;
	FTimerHandle TimerHandle_TeleportAttack;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UZInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UZAttributeComponent* AttributeComp;

	UFUNCTION()
	void MoveForward(float MoveValue);

	UFUNCTION()
	void MoveRight(float MoveValue);
 
	UFUNCTION()
	void BlackHoleAttack();

	UFUNCTION()
	void BlackHoleAttack_TimeElapsed();
	
	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void PrimaryAttack_TimeElapsed();

	UFUNCTION()
	void TeleportAttack();

	UFUNCTION()
	void TeleportAttack_TimeElapsed();

	// UFUNCTION()
	// void OnPrimaryAttack();

	UFUNCTION()
	void PrimaryInteract();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UZAttributeComponent* OwningComp, float NewHealth, float ChangedHealth);

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
