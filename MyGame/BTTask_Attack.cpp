// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "C_EnemyBase.h"
#include "C_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTTask_Attack::UBTTask_Attack() 
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingEnemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingEnemy == nullptr)
		return EBTNodeResult::Failed;

	ControllingEnemy->EnemyAttack();

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto ControllingEnemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingEnemy->bAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


