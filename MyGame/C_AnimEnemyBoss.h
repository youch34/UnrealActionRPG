// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_AnimEnemyBase.h"
#include "C_AnimEnemyBoss.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UC_AnimEnemyBoss : public UC_AnimEnemyBase
{
	GENERATED_BODY()
public:
    UC_AnimEnemyBoss();
public:
    void Skill1(UAnimMontage* Montage);
    void Skill2(UAnimMontage* Montage);
    void Skill3(UAnimMontage* Montage);
};
