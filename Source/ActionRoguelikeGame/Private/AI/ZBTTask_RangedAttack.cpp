// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"


EBTNodeResult::Type UZBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if(ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());

		if(MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if(TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_Front");
		FRotator MuzzleRotation = (TargetActor->GetActorLocation() - MuzzleLocation).Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation,Params);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}
