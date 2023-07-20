// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UZInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKEGAME_API AZCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZCharacter();

protected:

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;
	
	FTimerHandle TimerHandle_PrimaryAttack;

	UPROPERTY(EditAnywhere, Category="Attack")
	float PrimaryAttackDelayTime;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UZInteractionComponent* InteractionComp;

	UFUNCTION()
	void MoveForward(float MoveValue);

	UFUNCTION()
	void MoveRight(float MoveValue);

	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void PrimaryAttack_TimeElapsed();

	// UFUNCTION()
	// void OnPrimaryAttack();

	UFUNCTION()
	void PrimaryInteract();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
