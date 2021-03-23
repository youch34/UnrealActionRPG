// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDeco_IsInRange.h"
#include "C_Player.h"
#include "C_EnemyBase.h"
#include "C_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
bool UBTDeco_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Warning, TEXT("IsinRange"));

	auto ControllingEnemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingEnemy == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ControllingPawn"));
		return false;
	}

	auto Target = Cast<AC_Player>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AC_EnemyAIController::TargetKey));
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Target"));
		return false;
	}

	bResult = (ControllingEnemy->GetDistanceTo(Target) < ControllingEnemy->AttackRange);

	return bResult;
}