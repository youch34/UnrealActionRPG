// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimEnemyBoss.h"
#include "UObject/ConstructorHelpers.h"

UC_AnimEnemyBoss::UC_AnimEnemyBoss() 
{

	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage
	(
		TEXT("AnimMontage'/Game/Boss/Animation/Mon_Death.Mon_Death'")
	);
	if (deathmontage.Succeeded())
		DeathMontage = deathmontage.Object;
}

void UC_AnimEnemyBoss::Skill1(UAnimMontage* Montage) 
{
	Montage_Play(Montage);
}

void UC_AnimEnemyBoss::Skill2(UAnimMontage* Montage)
{
	Montage_Play(Montage);
}

void UC_AnimEnemyBoss::Skill3(UAnimMontage* Montage)
{
	Montage_Play(Montage);
}
