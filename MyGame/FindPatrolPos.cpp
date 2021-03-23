// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPos.h"
#include "BrainComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Engine/World.h"

#include "C_EnemyAIController.h"

UFindPatrolPos::UFindPatrolPos() 
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;
	
	FNavLocation NextPatrolPos;
	
	if (NavSystem->GetRandomPointInNavigableRadius(ControllingPawn->GetActorLocation(), 350.0f, NextPatrolPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AC_EnemyAIController::PatrolPosKey,NextPatrolPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
