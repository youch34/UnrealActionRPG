// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackSkillBase.generated.h"

UCLASS()
class MYGAME_API AAttackSkillBase : public AActor
{
	GENERATED_BODY()	  
	
public:	
	// Sets default values for this actor's properties
	AAttackSkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
		virtual void BeginOverlap
		(
			UPrimitiveComponent* OverComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	UFUNCTION(BlueprintCallable)
		virtual void ActiveBoxDamage();
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* ParticleComp;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Collision;

	UPROPERTY(VisibleDefaultsOnly)
		class UAudioComponent* Audio;
public:
	UPROPERTY(EditAnywhere, Category = "SKillSetting")
		bool bPlayerSkill;
	UPROPERTY(EditAnywhere, Category = "SKillSetting")
		float LifeTime;
	UPROPERTY(EditAnywhere, Category = "SkillStats")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "SkillStats")
		float DamageFactors;
};
