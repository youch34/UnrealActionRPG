// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_EnemyBase.h"
#include "C_EnemyMelee.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AC_EnemyMelee : public AC_EnemyBase
{
	GENERATED_BODY()
	
public:
	AC_EnemyMelee();

public:
	void BeginPlay() override;

public:
	void EnemyAttack() override;
	UFUNCTION(BlueprintCallable)
			void BasicFrontAttakc();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* AttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* CounterMesh;

	bool bCounter = false;
private:
	float counterTime = 0.5f;
};
