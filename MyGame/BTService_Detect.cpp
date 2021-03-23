// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "C_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


#include "C_Player.h"
#include "C_EnemyBase.h"

UBTService_Detect::UBTService_Detect() 
{
	NodeName = TEXT("Detect");
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingEnemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	DeadCheck(OwnerComp);

	if (ControllingEnemy == nullptr)
		return;

	UWorld* World = ControllingEnemy->GetWorld();
	FVector Center = ControllingEnemy->GetActorLocation();


	if (World == nullptr)
		return;

	float DetectRadius = ControllingEnemy->FollowRange;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingEnemy);

	bool bResult = World->OverlapMultiByProfile
	(
		OverlapResults,
		Center,
		FQuat::Identity,
		"Player",
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);


	if (bResult == true)
	{
		for (auto OverlapResult : OverlapResults)
		{
			if (AC_Player* Player = Cast<AC_Player>(OverlapResult.GetActor()))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AC_EnemyAIController::TargetKey, Player);
				ControllingEnemy->SetCombatState(true);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AC_EnemyAIController::TargetKey, nullptr);
	ControllingEnemy->SetCombatState(false);
}

void UBTService_Detect::DeadCheck(UBehaviorTreeComponent& OwnerComp)
{
	auto ControllingEnemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingEnemy == nullptr)
		return;

	if (ControllingEnemy->GetHp() <= 0)
	{
		ControllingEnemy->Death();
		OwnerComp.StopTree();
		return;
	}
}
