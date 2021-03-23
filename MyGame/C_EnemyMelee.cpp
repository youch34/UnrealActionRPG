// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyMelee.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "C_AnimEnemyMelee.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"


#include "C_Player.h"

AC_EnemyMelee::AC_EnemyMelee() 
	:AC_EnemyBase()
{
	CounterMesh = CreateDefaultSubobject<UStaticMeshComponent>("ConuterMesh");
	CounterMesh->AttachTo(GetMesh());
	CounterMesh->SetRelativeLocation(FVector(0,0,210));

	AttackBox = CreateDefaultSubobject<UBoxComponent>("AttackBox");
	AttackBox->AttachTo(GetMesh());
	AttackBox->SetRelativeLocation(FVector(200,0,100));
	AttackBox->SetCollisionProfileName("ESkill");
	CounterMesh->SetHiddenInGame(true);
}



void AC_EnemyMelee::BeginPlay()
{
	Super::BeginPlay();

	AttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AC_EnemyMelee::EnemyAttack()
{
	Super::EnemyAttack();
	if (bAttacking == true || bDamaged == true)
		return;
	bAttacking = true;
	if (AnimInstance)
	{
		if (bDamaged == false)
		{
			bCounter = true;
			CounterMesh->SetHiddenInGame(false);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() 
				{
					bCounter = false;
					CounterMesh->SetHiddenInGame(true);
				},counterTime,false);
			AnimInstance->Attack();
		}
	}
}

void AC_EnemyMelee::BasicFrontAttakc()
{
	TArray<FOverlapResult> Hits;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByProfile
	(
		Hits,
		AttackBox->GetComponentLocation(),
		FQuat::Identity,
		"ESkill",
		AttackBox->GetCollisionShape(),
		CollisionQueryParam
	);
	for (FOverlapResult hit : Hits)
	{
		UGameplayStatics::ApplyDamage(hit.GetActor(), AttackDamage, NULL, this, NULL);
	}
}

