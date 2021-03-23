// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimEnemyDistance.h"
#include "UObject/ConstructorHelpers.h"

UC_AnimEnemyDistance::UC_AnimEnemyDistance() 
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> attackmontage
	(
		TEXT("AnimMontage'/Game/EnemyDistance/Animation/Mon_SpellAttack.Mon_SpellAttack'")
	);
	if (attackmontage.Succeeded())
		AttackMontage = attackmontage.Object;
}