// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsCanAttack.h"
#include "C_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "C_Player.h"
#include "C_EnemyBase.h"

UBTService_IsCanAttack::UBTService_IsCanAttack() 
{
}

void UBTService_IsCanAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingEnemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingEnemy == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ControllingPawn"));
		return;
	}

	auto Target = Cast<AC_Player>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AC_EnemyAIController::TargetKey));
	if (Target == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Target"));
		return;
	}

	bool bCanAttack = (ControllingEnemy->GetDistanceTo(Target) < ControllingEnemy->AttackRange ? true : false);
	bool bCanMoveto = (ControllingEnemy->bAttacking == false && ControllingEnemy->bDamaged == false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AC_EnemyAIController::bCanAttackKey, bCanAttack);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AC_EnemyAIController::bCanMovetoKey, bCanMoveto);

}