// Fill out your copyright notice in the Description page of Project Settings.


#include "ZCharacter.h"

#include "DrawDebugHelpers.h"
#include "ZInteractionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AZCharacter::AZCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UZInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	PrimaryAttackDelayTime = 0.2f;
}

// Called when the game starts or when spawned
void AZCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZCharacter::MoveForward(float MoveValue)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Pitch = 0;
	ControllerRot.Roll = 0;

	AddMovementInput(ControllerRot.Vector(), MoveValue);
}

void AZCharacter::MoveRight(float MoveValue)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Pitch = 0;
	ControllerRot.Roll = 0;

	FVector RightVector = FRotationMatrix(ControllerRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, MoveValue);
}

// Called every frame
void AZCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AZCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AZCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookAt", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed, this, &AZCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("BlackHoleAttack",IE_Pressed, this, &AZCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AZCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("TeleportAttack", IE_Pressed, this, &AZCharacter::TeleportAttack);

}

void AZCharacter::PrimaryAttack() 
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AZCharacter::PrimaryAttack_TimeElapsed, PrimaryAttackDelayTime);
	
	// FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	//
	// FTransform SpawnTM = FTransform(GetControlRotation(), SpawnLocation);
	//
	// FActorSpawnParameters SpawnParams;
	// SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//
	// GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void AZCharacter::PrimaryAttack_TimeElapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	APlayerController* CurPC = Cast<APlayerController>(Controller);
	FVector ViewLocation, ViewDir;
	CurPC->DeprojectMousePositionToWorld(ViewLocation, ViewDir);

	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	//DrawDebugLine(GetWorld(), ViewLocation, ViewLocation + GetControlRotation().Vector() * 10000, FColor::Blue, false, 2.0f, 0 , 2.0f);
	
	GetWorld()->LineTraceSingleByObjectType(Hit, ViewLocation, ViewLocation + GetControlRotation().Vector() * 10000, ObjectQueryParams);

	FRotator SpawnRotation;
	if(Hit.GetActor())
	{
		SpawnRotation = (Hit.Location - SpawnLocation).Rotation();
	}
	else
	{
		SpawnRotation = ((GetControlRotation().Vector() * 10000 + ViewLocation) - SpawnLocation).Rotation();
	}
    //FTransform SpawnTM = FTransform(GetControlRotation(), SpawnLocation);
    FTransform SpawnTM = FTransform(SpawnRotation, SpawnLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.Instigator = this;

    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	
}

// void AZCharacter::OnPrimaryAttack()
// {
// 	FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");
//
// 	FTransform SpawnTM = FTransform(GetControlRotation(), SpawnLocation);
//
// 	FActorSpawnParameters SpawnParams;
// 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	SpawnParams.Instigator = this;
//
// 	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
// }

void AZCharacter::PrimaryInteract() 
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AZCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack, this, &AZCharacter::BlackHoleAttack_TimeElapsed, BlackHoleAttackDelayTime);
}

void AZCharacter::BlackHoleAttack_TimeElapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	APlayerController* CurPC = Cast<APlayerController>(Controller);
	FVector ViewLocation, ViewDir;
	CurPC->DeprojectMousePositionToWorld(ViewLocation, ViewDir);

	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	//DrawDebugLine(GetWorld(), ViewLocation, ViewLocation + GetControlRotation().Vector() * 10000, FColor::Blue, false, 2.0f, 0 , 2.0f);
	
	GetWorld()->LineTraceSingleByObjectType(Hit, ViewLocation, ViewLocation + GetControlRotation().Vector() * 10000, ObjectQueryParams);

	FRotator SpawnRotation;
	if(Hit.GetActor())
	{
		SpawnRotation = (Hit.Location - SpawnLocation).Rotation();
	}
	else
	{
		SpawnRotation = ((GetControlRotation().Vector() * 10000 + ViewLocation) - SpawnLocation).Rotation();
	}
	//FTransform SpawnTM = FTransform(GetControlRotation(), SpawnLocation);
	FTransform SpawnTM = FTransform(SpawnRotation, SpawnLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(BlackHoleProjectileClass, SpawnTM, SpawnParams);
	
}

void AZCharacter::TeleportAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportAttack, this, &AZCharacter::TeleportAttack_TimeElapsed, TeleportAttackDelayTime);
}

void AZCharacter::TeleportAttack_TimeElapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	APlayerController* CurPC = Cast<APlayerController>(Controller);
	FVector ViewLocation, ViewDir;
	CurPC->DeprojectMousePositionToWorld(ViewLocation, ViewDir);

	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	//DrawDebugLine(GetWorld(), ViewLocation, ViewLocation + GetControlRotation().Vector() * 10000, FColor::Blue, false, 2.0f, 0 , 2.0f);
	
	GetWorld()->LineTraceSingleByObjectType(Hit, ViewLocation, ViewLocation + GetControlRotation().Vector() * 10000, ObjectQueryParams);

	FRotator SpawnRotation;
	if(Hit.GetActor())
	{
		SpawnRotation = (Hit.Location - SpawnLocation).Rotation();
	}
	else
	{
		SpawnRotation = ((GetControlRotation().Vector() * 10000 + ViewLocation) - SpawnLocation).Rotation();
	}
	//FTransform SpawnTM = FTransform(GetControlRotation(), SpawnLocation);
	FTransform SpawnTM = FTransform(SpawnRotation, SpawnLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(TeleportProjectileClass, SpawnTM, SpawnParams);
	
}

