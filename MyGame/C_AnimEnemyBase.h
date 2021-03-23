// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AnimEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UC_AnimEnemyBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UC_AnimEnemyBase();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly)
		float MoveSpeed;
	UPROPERTY(BlueprintReadOnly)
		float Direction;
	UPROPERTY(BlueprintReadOnly)
		bool bCombatState;

public:
	UFUNCTION(BlueprintCallable)
		virtual void Attack();
	UFUNCTION(BlueprintCallable)
		virtual void OnEndAttack();
	UFUNCTION(BlueprintCallable)
		virtual void Damaged();
	UFUNCTION(BlueprintCallable)
		virtual void Death();

public:
	FName GetNormalAttackMontageSection(int SectionNum);
	void JumpToAttackMontageSection(int SectionNum);
public:
	class AC_EnemyBase* Character;

public:
	class UAnimMontage* DamagedMontage;
	class UAnimMontage* AttackMontage;
	class UAnimMontage* DeathMontage;
};
