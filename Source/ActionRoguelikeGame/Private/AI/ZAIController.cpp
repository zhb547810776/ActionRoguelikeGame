// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AZAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehiviorTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if(MyPawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s", *MyPawn->GetActorLabel()));
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation",MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);

		//GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}
