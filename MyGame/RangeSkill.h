// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackSkillBase.h"
#include "RangeSkill.generated.h"

UCLASS()
class MYGAME_API ARangeSkill : public AAttackSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangeSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditDefaultsOnly)
		class USoundCue* ExplosionSound;
public:
	//0 ~ 1;
	UPROPERTY(EditAnywhere)
		float ActiveTimeRate;

	bool ActiveEnd;
	float CurrentTIme;
};
