// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JsonManager.h"
#include "C_Player.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemUsed);

UCLASS()
class MYGAME_API AC_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Player();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintAssignable)
		FItemUsed ItemUsed;
//Components
public:
	class UC_AnimPlayer* AnimInstance;
	//UPROPERTY(VisibleDefaultsOnly)
	//	class USpringArmComponent* Arm;
	//
	//UPROPERTY(VisibleDefaultsOnly)
	//    class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* SkyCamera;

	UPROPERTY(VisibleDefaultsOnly)
		class UAudioComponent* Audio;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBoxComponent* WeaponCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* Skill1SpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* Skill2SpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* Skill3SpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USkeletalMeshComponent* WeaponMesh;
	class USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		class AItem_Weapon* CurrentWeapon;
	UFUNCTION(BlueprintCallable)
		class AItem_Weapon* GetCurWeapon();
	void SetCurWeapon(AItem_Weapon* weapon);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
		void OnEndAttack();
public:
	void MoveRight(float val);
	void MoveForward(float val);
	void Turn(float val);
	void LookUp(float val);
	void RunPressed();
	void MouseLeft();
	void ResetCombo();
	UFUNCTION(BlueprintCallable)
		void LookAt(FVector GoalVec);
	UFUNCTION(BlueprintCallable)
		void UseItem(class AItem* item);
	UFUNCTION(BlueprintCallable)
		void Action();
//Combat-----------------------------------
public:
	UFUNCTION(BlueprintCallable)
		void BasicFrontAttack();
	//Special Attack
	UFUNCTION(BlueprintCallable)
		void FourthAttack();
	UFUNCTION(BlueprintCallable)
		void Skill1();
	UFUNCTION(BlueprintCallable)
		void Skill2();
	UFUNCTION(BlueprintCallable)
		void Skill3();
	void CalcSkillCool(float deltaTime);
	bool IsCoolTime(int num);

	void Dash();
	void BackDash();

	class AC_EnemyMelee* CheckCounter();
	UFUNCTION(BlueprintCallable)
		void CounterAttack();

	virtual float TakeDamage(
		float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	void EndDamage();
//State------------------------------
public:
	bool IsRunning() { return bRunning; }
	bool IsAttacking() { return bAttacking; }
	void SetMaterial(FVector vec);
	void SetHitStateImmune(bool val) { HitStateImmune = val; }
	USceneComponent* GetRootComponent() { return RootComponent; }
//StatsFunc
public:
	UFUNCTION(BlueprintCallable)
		void AddExp(float val);
	UFUNCTION(BlueprintCallable)
		void LevelUp();

public:
	//Stats
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerStat")
		float MaxHp;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerStat")
		float Hp;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerStat")
		float ATKPow;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerStat")
		int Level = 1;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerStat")
		float MaxExp = 200;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerStat")
		float CurExp = 0;
	//State
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerState")
		bool bRunning = false;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerState")
		bool bAttacking = false;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerState")
		bool bDamaged = false;
	UPROPERTY(BluePrintReadOnly, EditDefaultsOnly, Category = "PlayerState")
		bool bEvade = false;

	bool HitStateImmune;
//공격 콤보관련 변수
	int32 CurrentCombo;
	int32 MaxCombo;
	bool bNextCombo = false;

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<float> skillCool = {5.0f, 3.0f, 10.0f};
	UPROPERTY(BlueprintReadOnly)
		TArray<float> curSkillCool { 0.0f, 0.0f, 0.0f };
//Spawn Actors, Particles
public:
	UPROPERTY(EditDefaultsOnly, Category = "AttackParticle")
		TSubclassOf<AActor> FourthAttackParticle;
	UPROPERTY(EditDefaultsOnly, Category = "AttackParticle")
		TSubclassOf<AActor> Skill1Particle;
	UPROPERTY(EditDefaultsOnly, Category = "AttackParticle")
		TSubclassOf<AActor> Skill2Particle;
	UPROPERTY(EditDefaultsOnly, Category = "AttackParticle")
		TSubclassOf<AActor> Skill3Particle;
	UPROPERTY(EditDefaultsOnly, Category = "Particle")
		TSubclassOf<AActor> LevelUpEffect;

//Material
public:
	UPROPERTY(EditDefaultsOnly, Category = "Material")
		FVector DefaultColor;
	UPROPERTY(EditDefaultsOnly, Category = "Material")
		FVector DamagedColor;
	UPROPERTY(EditDefaultsOnly, Category = "Material")
		TArray<class UMaterial*> Mat_Bodys;
	TArray<class UMaterialInstanceDynamic*> Mat_BodyInstances;
//Sound
public:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* LevelupSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* HealSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* DefaultFootstep;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* GrassFootstep;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* PickUp;
	UFUNCTION(BlueprintCallable)
		void PlayFootstepSound();
//Json
private:
	class JsonManager Jm;
	void SavePlayerInfo();
	void LoadPlayerInfo();

};
