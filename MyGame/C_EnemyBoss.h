// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_EnemyBase.h"
#include "C_EnemyBoss.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AC_EnemyBoss : public AC_EnemyBase
{
	GENERATED_BODY()
	
public:
	AC_EnemyBoss();
public:
	void EnemyAttack() override;

	void PostInitializeComponents() override;

	void BeginPlay() override;
public:
	void SetCombatState(bool val) override;

public:
		virtual float TakeDamage(
			float Damage,
			struct FDamageEvent const& DamageEvent,
			AController* EventInstigator,
			AActor* DamageCauser) override;
public:
	void Skill1();
	UFUNCTION(BlueprintCallable)
		void SpawnSkill1();
	void Skill2();
	UFUNCTION(BlueprintCallable)
		void SpawnSkill2();
	void Skill3();
	UFUNCTION(BlueprintCallable)
		void SpawnSkill3();
public:
	UPROPERTY(EditDefaultsOnly, Category = "SkillParticle")
		TSubclassOf<AActor> Skill1Particle;
	UPROPERTY(EditDefaultsOnly, Category = "SkillMontage")
		UAnimMontage* Skill1Montage;
	USceneComponent* Skill1SpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category = "SkillParticle")
		TSubclassOf<class  APeriodSpawnActor> Skill2Particle;
	UPROPERTY(EditDefaultsOnly, Category = "SkillMontage")
		UAnimMontage* Skill2Montage;
	USceneComponent* Skill2SpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category = "SkillParticle")
		TSubclassOf<class AActor> Skill3Particle;
	UPROPERTY(EditDefaultsOnly, Category = "SkillMontage")
		UAnimMontage* Skill3Montage;
public:
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetting")
		float Skill3Num;
public:
	UPROPERTY(EditDefaultsOnly, Category = "SkillRange")
		TArray<float> SkillRanges;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* DamageSound;
private:
	class UC_AnimEnemyBoss* AnimBoss;

	TArray<void(AC_EnemyBoss::*)()> Skills;
};
