// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileSkill.h"
#include "Projectile_TickDamage.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AProjectile_TickDamage : public AProjectileSkill
{
	GENERATED_BODY()
public:
	AProjectile_TickDamage();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "SKillSetting")
		float TickTime;

	float CurrentTime;
	bool bStarted = false;
};
