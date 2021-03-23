// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "C_EnemyBase.h"

UC_AnimEnemyBase::UC_AnimEnemyBase() 
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> damagedmontage
	(
		TEXT("AnimMontage'/Game/Enemy/Animation/Mon_Damaged.Mon_Damaged'")
	);
	if (damagedmontage.Succeeded())
		DamagedMontage = damagedmontage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage
	(
		TEXT("AnimMontage'/Game/Enemy/Animation/Mon_Death.Mon_Death'")
	);
	if (deathmontage.Succeeded())
		DeathMontage = deathmontage.Object;
}

void UC_AnimEnemyBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<AC_EnemyBase>(TryGetPawnOwner());
}

void UC_AnimEnemyBase::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Character == NULL)
		return;

	if (Character && Character->IsValidLowLevel())
	{
		MoveSpeed = Character->GetCharacterMovement()->Velocity.Size();
		Direction = CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
		bCombatState = Character->bCombatState;
	}
}

FName UC_AnimEnemyBase::GetNormalAttackMontageSection(int SectionNum)
{
	return FName(*FString::Printf(TEXT("ATT%d"), SectionNum));
}

void UC_AnimEnemyBase::JumpToAttackMontageSection(int NewSection)
{
	Montage_JumpToSection(GetNormalAttackMontageSection(NewSection));
}

void UC_AnimEnemyBase::Attack()
{
	if (AttackMontage)
	{
		Montage_Stop(NULL);
		Montage_Play(AttackMontage);
	}
}

void UC_AnimEnemyBase::OnEndAttack()
{
	Character->OnEnemyEndAttack();
}

void UC_AnimEnemyBase::Damaged()
{
	Montage_Stop(NULL);
	Montage_Play(DamagedMontage);
}

void UC_AnimEnemyBase::Death()
{
	Montage_Stop(NULL);
	Montage_Play(DeathMontage);
}
