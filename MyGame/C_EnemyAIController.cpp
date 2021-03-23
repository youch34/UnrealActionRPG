// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AC_EnemyAIController::HomePosKey(TEXT("HomePos"));
const FName AC_EnemyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AC_EnemyAIController::TargetKey(TEXT("Target"));
const FName AC_EnemyAIController::bAttackKey(TEXT("bAttacking"));
const FName AC_EnemyAIController::bCanAttackKey(TEXT("bCanAttack"));
const FName AC_EnemyAIController::bCanMovetoKey(TEXT("bCanMoveto"));




AC_EnemyAIController::AC_EnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> btenemy
	(
		TEXT("BehaviorTree'/Game/AI/BT_Enemy2.BT_Enemy2'")
	);
	if (btenemy.Succeeded())
		BTEnemy = btenemy.Object;
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> bbenemy
	(
		TEXT("BlackboardData'/Game/AI/BB_Enemy.BB_Enemy'")
	);
	if (bbenemy.Succeeded())
		BBEnemy = bbenemy.Object;
}

void AC_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if(BTEnemy)
		RunBehaviorTree(BTEnemy);
}
