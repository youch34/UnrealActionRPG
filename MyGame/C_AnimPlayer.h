// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AnimPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UC_AnimPlayer : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UC_AnimPlayer();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaTime) override;

public:
	//About Combo Attack
	void Attack();
	FName GetNormalAttackMontageSection(int SectionNum);
	void JumpToAttackMontageSection(int SectionNum);

	//Damaged
	void Damaged();
	UFUNCTION(BlueprintCallable)
		void EndDamaged();

	//Aboud Charactor Dash
	UFUNCTION(BlueprintCallable)
		void Dash();
	UFUNCTION(BlueprintCallable)
		void StopDash();
	UFUNCTION(BlueprintCallable)
		void BackDash();

	bool bCanDash;
	float DashCoolDown;
	float DashDistancePerTick;
	bool bDashing;

public:
	//Skill
	UFUNCTION(BlueprintCallable)
		void Skill1();
	UFUNCTION(BlueprintCallable)
		void Skill2();
	UFUNCTION(BlueprintCallable)
		void Skill3();
	UFUNCTION(BlueprintCallable)
		void CounterAttack();
	UFUNCTION(BlueprintCallable)
		void LaunchSkill1();
	UFUNCTION(BlueprintCallable)
		void LaunchSkill2();
	UFUNCTION(BlueprintCallable)
		void LaunchSkill3();
public:
	class UAnimMontage* NormalAttacks;
	class UAnimMontage* DashMontage;
	class UAnimMontage* BackDashMontage;
	class UAnimMontage* Skill1Montage;
	class UAnimMontage* Skill2Montage;
	class UAnimMontage* Skill3Montage;
	class UAnimMontage* CounterAttackMontage;
	class UAnimMontage* DamagedMontage;

public:
	UPROPERTY(BlueprintReadOnly)
		float MoveSpeed;
	UPROPERTY(BlueprintReadOnly)
		bool bEquipWeapon;
private:
	class AC_Player* Player;
	FTimerHandle TimeHandle;
};
