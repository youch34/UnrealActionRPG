// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_EnemyBase.h"
#include "C_EnemyDistance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AC_EnemyDistance : public AC_EnemyBase
{
	GENERATED_BODY()
public:
	AC_EnemyDistance();

	void BeginPlay() override;
public:
	
	void EnemyAttack() override;
	UFUNCTION(BlueprintCallable)
		void SpawnNormalAttack();
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		USceneComponent* NormalAttackPoint;
	UPROPERTY(EditDefaultsOnly, Category = "AttackParticle")
		TSubclassOf<AActor> NormalAttackParticle;

};
