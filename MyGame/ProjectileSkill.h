// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackSkillBase.h"
#include "ProjectileSkill.generated.h"

UCLASS()
class MYGAME_API AProjectileSkill : public AAttackSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void BeginOverlap
	(
		UPrimitiveComponent* OverComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;
public:
	UPROPERTY(EditDefaultsOnly, Category = "ExplosionParticle")
		TSubclassOf<AActor> ExplosionParticle;
public:
	UPROPERTY(EditDefaultsOnly, Category = "SKillSetting")
		bool bExplosion;
};
