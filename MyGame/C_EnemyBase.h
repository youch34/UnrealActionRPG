// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_EnemyBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEndAttackDelegate)

UCLASS()
class MYGAME_API AC_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_EnemyBase();

	void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
public:
	//Behavior, Action
	UFUNCTION(BlueprintCallable)
		virtual void EnemyAttack();
	UFUNCTION(BlueprintCallable)
		virtual void OnEnemyEndAttack();
	UFUNCTION(BlueprintCallable)
		virtual void Damaged();
	UFUNCTION(BlueprintCallable)
		virtual float TakeDamage(
			float Damage,
			struct FDamageEvent const& DamageEvent,
			AController* EventInstigator,
			AActor* DamageCauser) override;
	UFUNCTION(BlueprintImplementableEvent)
		void BPTakeDamage(float damage);
	UFUNCTION(BlueprintCallable)
		virtual void EndDamaged();
	UFUNCTION(BlueprintCallable)
		virtual void BePushed();
	UFUNCTION(BlueprintCallable)
		virtual void Observe() {}
	UFUNCTION(BlueprintCallable)
		virtual void FollowPlayer() {}

public:
	virtual void SetCombatState(bool val);
	void SetAttackRange(float val);
	void SetMaterial(FVector Color);
	FORCEINLINE float GetHp() { return Hp; }
	FORCEINLINE bool IsDamaged() { return bDamaged; }

	void DropItem();
	void Death();
public:
	//State
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float MaxHp;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float Hp;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float AttackDamage;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float AttackRange;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float FollowRange;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float AttackDelay;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "HitSetting")
		bool HitActionImmune;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "State")
		bool bAttacking = false;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "State")
		bool bDamaged = false;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "State")
		bool bCombatState = false;
	UPROPERTY(BluePrintReadOnly, EditAnywhere, Category = "State")
		float Exp;
	UPROPERTY(BluePrintReadOnly)
		bool bDead = false;
	float StuckTime = 1.0f;
//Components
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UAudioComponent* Audio;
		
public:
	UPROPERTY(EditDefaultsOnly, Category = "HitSetting")
		FVector DefaultColor;
	UPROPERTY(EditDefaultsOnly, Category = "HitSetting")
		FVector DamagedColor;
public:
	FOnEndAttackDelegate OnEndAttack;
//TimeHandler
public:
	FTimerHandle EndAttackTimer;
	FTimerHandle EndDamageTimer;
public:
	class UC_AnimEnemyBase* AnimInstance;

	//피격 효과를 위한 머티리얼 변수
	UPROPERTY(EditDefaultsOnly, Category = "Material")
		TArray<class UMaterial*> Mat_Bodys;
	TArray<class UMaterialInstanceDynamic*> Mat_BodyInstances;

	//드랍할 아이템
	UPROPERTY(EditDefaultsOnly, Category = "DropItem")
		TSubclassOf<class AFoodItem> Potion;
public:
};
