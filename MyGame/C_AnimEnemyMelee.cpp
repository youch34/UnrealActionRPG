// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimEnemyMelee.h"
#include "UObject/ConstructorHelpers.h"

UC_AnimEnemyMelee::UC_AnimEnemyMelee() 
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> attackmontage
	(
		TEXT("AnimMontage'/Game/Enemy/Animation/Mon_MeleeAttack.Mon_MeleeAttack'")
	);
	if (attackmontage.Succeeded())
		AttackMontage = attackmontage.Object;

}
