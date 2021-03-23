// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyBoss.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "C_AnimEnemyBase.h"
#include "C_AnimEnemyBoss.h"
#include "PeriodSpawnActor.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"

AC_EnemyBoss::AC_EnemyBoss() 
{
	static ConstructorHelpers::FObjectFinder<USoundCue> damagesound
	(
		TEXT("SoundCue'/Game/Sound/Cue_Damaged.Cue_Damaged'")
	);
	if (damagesound.Succeeded())
		DamageSound = damagesound.Object;
}

void AC_EnemyBoss::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimBoss = Cast<UC_AnimEnemyBoss>(GetMesh()->GetAnimInstance());
}

void AC_EnemyBoss::BeginPlay()
{
	Super::BeginPlay();
	TSet<UActorComponent*> components = this->GetComponents();
	for (UActorComponent* component : components)
	{
		FString name = component->GetName();
		if (name == "SKill1SpawnPoint")
		{
			Skill1SpawnPoint = Cast<USceneComponent>(component);
		}
		if (name == "SKill2SpawnPoint")
		{
			Skill2SpawnPoint = Cast<USceneComponent>(component);
		}
	}
	Skills.Add(&AC_EnemyBoss::Skill1);
	Skills.Add(&AC_EnemyBoss::Skill2);
	Skills.Add(&AC_EnemyBoss::Skill3);

	AttackRange = SkillRanges[0];

}

void AC_EnemyBoss::SetCombatState(bool val)
{
	Super::SetCombatState(val);
	if (val == true)
	{
	}
}

void AC_EnemyBoss::EnemyAttack()
{
	Super::EnemyAttack();
	if (bAttacking == true || bDamaged == true)
		return;
	bAttacking = true;
	static int curskill = 0;
	//int NumSkill = Skills.Num();
	//int rand = FMath::RandRange(0,NumSkill-1);
	//(this->*Skills[rand])();
	(this->*Skills[curskill])();
	curskill++;
	if (curskill == 3)
		curskill = 0;
	AttackRange = SkillRanges[curskill];
}


float AC_EnemyBoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Audio->SetSound(DamageSound);
	Audio->Play();
	return Damage;
}

void AC_EnemyBoss::Skill1()
{
	AnimBoss->Skill1(Skill1Montage);
}

void AC_EnemyBoss::SpawnSkill1()
{
	GetWorld()->SpawnActor<AActor>(Skill1Particle, Skill1SpawnPoint->GetComponentLocation(),
									GetActorRotation());
}

void AC_EnemyBoss::Skill2()
{
	AnimBoss->Skill2(Skill2Montage);
}

void AC_EnemyBoss::SpawnSkill2()
{
	APeriodSpawnActor* skill2 = GetWorld()->SpawnActor<APeriodSpawnActor>(Skill2Particle, GetActorLocation(),
		GetActorRotation());
	skill2->Init(3000, 3000, Skill2SpawnPoint->GetComponentLocation().Z);
	FTimerHandle TimeHandle;
	GetWorld()->GetTimerManager().SetTimer
	(
		TimeHandle,
		[this]() { AnimBoss->JumpToAttackMontageSection(1);  },
		skill2->GetCastTime(),false
	);
}

void AC_EnemyBoss::Skill3()
{
	AnimBoss->Skill3(Skill3Montage);
}

void AC_EnemyBoss::SpawnSkill3()
{
	FVector Location = GetActorLocation();
	Location.Z -= 100;
	FVector Rot = GetActorRotation().Euler();
	float PerDegree = 360 / Skill3Num;
	for (int i = 0; i < Skill3Num; i++) 
	{
		Rot.Z += PerDegree * i;
		GetWorld()->SpawnActor<AActor>(Skill3Particle,Location,FRotator::MakeFromEuler(Rot));
	}
}
