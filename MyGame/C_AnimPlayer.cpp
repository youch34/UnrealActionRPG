// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Animation/BlendSpace1D.h"

#include "C_Player.h"
#include "ProjectileSkill.h"

UC_AnimPlayer::UC_AnimPlayer() 
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> normalattacks
	(
		TEXT("AnimMontage'/Game/Player/Animation/NormalAttacks.NormalAttacks'")
	);
	if (normalattacks.Succeeded())
		NormalAttacks = normalattacks.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> dashmontage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_Dash.Mon_Dash'")
	);
	if (dashmontage.Succeeded())
		DashMontage = dashmontage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> backdashmontage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_BackDash.Mon_BackDash'")
	);
	if (backdashmontage.Succeeded())
		BackDashMontage = backdashmontage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> skill1montage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_Skill1.Mon_Skill1'")
	);
	if (skill1montage.Succeeded())
		Skill1Montage = skill1montage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> skill2montage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_Skill2.Mon_Skill2'")
	);
	if (skill2montage.Succeeded())
		Skill2Montage = skill2montage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> skill3montage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_Skill3.Mon_Skill3'")
	);
	if (skill3montage.Succeeded())
		Skill3Montage = skill3montage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> countermontage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_CounterAttack'")
	);
	if (countermontage.Succeeded())
		CounterAttackMontage = countermontage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> damagedmontage
	(
		TEXT("AnimMontage'/Game/Player/Animation/Mon_Damaged.Mon_Damaged'")
	);
	if (damagedmontage.Succeeded())
		DamagedMontage = damagedmontage.Object;
}

void UC_AnimPlayer::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<AC_Player>(TryGetPawnOwner());

	bCanDash = true;
	DashCoolDown = 2.0f;
	DashDistancePerTick = 10.0f;
}

void UC_AnimPlayer::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Player == NULL)
		return;

	//캐릭터의 상태를 업데이트
	if (Player && Player->IsValidLowLevel())
	{
		MoveSpeed = Player->GetCharacterMovement()->Velocity.Size();
		bEquipWeapon = Player->GetCurWeapon() ? true : false;
	}

	if (bDashing == true)
	{
		Player->GetRootComponent()->MoveComponent
		(
			Player->GetActorForwardVector()* DashDistancePerTick,
			Player->GetActorRotation(), false
		);
	}
}

void UC_AnimPlayer::Attack()
{
	Montage_Play(NormalAttacks);
}

FName UC_AnimPlayer::GetNormalAttackMontageSection(int SectionNum)
{
	return FName(*FString::Printf(TEXT("ATT%d"), SectionNum));
}

void UC_AnimPlayer::JumpToAttackMontageSection(int NewSection)
{
	Montage_JumpToSection(GetNormalAttackMontageSection(NewSection), NormalAttacks);
}

void UC_AnimPlayer::Damaged()
{
	Montage_Play(DamagedMontage);
}

void UC_AnimPlayer::EndDamaged()
{
	Player->bDamaged = false;
	Player->ResetCombo();
	Player->EndDamage();
}

void UC_AnimPlayer::Dash()
{
	if (bCanDash == true)
	{
		bDashing = true;
		bCanDash = false;
		Montage_Play(DashMontage);
		GetWorld()->GetTimerManager().SetTimer
		(
			TimeHandle,
			[this]() { bCanDash = true; }, DashCoolDown, false
		);
	}
}

void UC_AnimPlayer::StopDash()
{
	DashDistancePerTick = 10.0f;
	bDashing = false;
}

void UC_AnimPlayer::BackDash()
{
	if (bCanDash == true)
	{
		bDashing = true;
		bCanDash = false;
		Montage_Play(BackDashMontage);
		GetWorld()->GetTimerManager().SetTimer
		(
			TimeHandle,
			[this]() { bCanDash = true; }, DashCoolDown, false
		);
		DashDistancePerTick *= -1.0f;
	}
}

void UC_AnimPlayer::Skill1()
{
	Montage_Play(Skill1Montage);
}

void UC_AnimPlayer::Skill2()
{
	Montage_Play(Skill2Montage);
}

void UC_AnimPlayer::Skill3()
{
	Montage_Play(Skill3Montage);
}

void UC_AnimPlayer::CounterAttack()
{
	Montage_Play(CounterAttackMontage);
}

void UC_AnimPlayer::LaunchSkill1()
{
	FVector Location = Player->Skill1SpawnPoint->GetComponentLocation();
	auto particle = Player->GetWorld()->SpawnActor<AActor>(Player->Skill1Particle, Location, Player->GetActorRotation());
	if (auto Skill = Cast<AAttackSkillBase>(particle))
	{
		Skill->Damage = Player->ATKPow;
	}
}

void UC_AnimPlayer::LaunchSkill2()
{
	FVector Location = Player->Skill2SpawnPoint->GetComponentLocation();
	auto particle = Player->GetWorld()->SpawnActor<AActor>(Player->Skill2Particle, Location, Player->GetActorRotation());
	if (auto Skill = Cast<AAttackSkillBase>(particle))
	{
		Skill->Damage = Player->ATKPow;
	}
}

void UC_AnimPlayer::LaunchSkill3()
{
	FVector Location = Player->Skill3SpawnPoint->GetComponentLocation();
	auto particle = Player->GetWorld()->SpawnActor<AActor>(Player->Skill3Particle, Location, Player->GetActorRotation());
	if (auto Skill = Cast<AAttackSkillBase>(particle))
	{
		Skill->Damage = Player->ATKPow;
	}
}

