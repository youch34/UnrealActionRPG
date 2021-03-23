// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AC_EnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AC_EnemyAIController();
public:
	void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		UBehaviorTree* BTEnemy;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		UBlackboardData* BBEnemy;
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName bAttackKey;
	static const FName bCanAttackKey;
	static const FName bCanMovetoKey;

};
