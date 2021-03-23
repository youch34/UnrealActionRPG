// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyDistance.h"
#include "C_AnimEnemyDistance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AC_EnemyDistance::AC_EnemyDistance() 
{
	NormalAttackPoint = CreateDefaultSubobject<USceneComponent>("NormalAttackPoint");
	NormalAttackPoint->AttachTo(GetMesh());
}


void AC_EnemyDistance::BeginPlay()
{
	Super::BeginPlay();
	TSet<UActorComponent*> components = this->GetComponents();
}

void AC_EnemyDistance::SpawnNormalAttack()
{
	GetWorld()->SpawnActor<AActor>(NormalAttackParticle, NormalAttackPoint->GetComponentLocation(), GetActorRotation());
}

void AC_EnemyDistance::EnemyAttack()
{
	Super::EnemyAttack();

	if (bAttacking == true || bDamaged == true)
		return;
	bAttacking = true;
	if(AnimInstance)
		AnimInstance->Attack();
}