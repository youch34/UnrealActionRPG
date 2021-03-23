// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyBase.h"
#include "DrawDebugHelpers.h"
#include "C_EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

#include "C_AnimEnemyBase.h"
#include "DamageDisplay.h"
#include "FoodItem.h"
#include "C_Player.h"
// Sets default values
AC_EnemyBase::AC_EnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Audio = CreateDefaultSubobject<UAudioComponent>("AudioComponent");

	AIControllerClass = AC_EnemyAIController::StaticClass();
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttackDelay = 1.5f;

	bAttacking = false;

}	

void AC_EnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	AnimInstance = Cast<UC_AnimEnemyBase>(GetMesh()->GetAnimInstance());
}

// Called when the game starts or when spawned
void AC_EnemyBase::BeginPlay()
{
	Super::BeginPlay();

	TSet<UActorComponent*> components = this->GetComponents();
	for (UActorComponent* component : components)
	{
	}
	SetCombatState(false);
	for (int i = 0; i < Mat_Bodys.Num(); i++)
	{
		Mat_BodyInstances.Add(UMaterialInstanceDynamic::Create(Mat_Bodys[i], this));
		GetMesh()->SetMaterial(i, Mat_BodyInstances[i]);
		Mat_BodyInstances[i]->SetVectorParameterValue("BaseColor", DefaultColor);
	}

	Hp = MaxHp;
}

// Called every frame
void AC_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_EnemyBase::EnemyAttack()
{
}

void AC_EnemyBase::OnEnemyEndAttack()
{
	GetWorld()->GetTimerManager().SetTimer(EndAttackTimer, [this]()
		{
			OnEndAttack.Broadcast();
			bAttacking = false;
		}, AttackDelay, false);
}

void AC_EnemyBase::Damaged()
{
	GetWorldTimerManager().ClearTimer(EndDamageTimer);
	bDamaged = true;
	GetWorld()->GetTimerManager().SetTimer(EndDamageTimer, [this]()
		{
			bDamaged = false;
		}, StuckTime, false);
}

float AC_EnemyBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Result = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Hp -= Damage;
	//피격 머테리얼 전환
	SetMaterial(DamagedColor);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { SetMaterial(DefaultColor); }, 0.3, false);
	//데미지 표시 위젯 생성 in 블루프린트
	BPTakeDamage(Damage);
	if (HitActionImmune == true)
	{
		return Result;
	}
	GetWorldTimerManager().ClearTimer(EndAttackTimer);
	bAttacking = false;
	Damaged();
	BePushed();
	if(AnimInstance)
		AnimInstance->Damaged();

	return Result;
}

void AC_EnemyBase::EndDamaged()
{
}

void AC_EnemyBase::BePushed()
{
	if (HitActionImmune != true)
		LaunchCharacter(GetActorForwardVector() * -500.0f, false, false);
}

void AC_EnemyBase::SetCombatState(bool val)
{
	if (val == true)
	{
		bCombatState = val;
		GetCharacterMovement()->MaxWalkSpeed = 500;
	}
	else 
	{
		bCombatState = val;
		GetCharacterMovement()->MaxWalkSpeed = 100;
	}
}

void AC_EnemyBase::SetAttackRange(float val)
{
	AttackRange = val;
}

void AC_EnemyBase::SetMaterial(FVector Color)
{
	for (int i = 0; i < Mat_Bodys.Num(); i++)
	{
		Mat_BodyInstances[i]->SetVectorParameterValue("BaseColor", Color);
	}
}



void AC_EnemyBase::DropItem()
{
	FVector SpawnPos = GetActorLocation();
	SpawnPos.Z = 0;
	GetWorld()->SpawnActor<AFoodItem>(Potion,SpawnPos,GetActorRotation());
}

void AC_EnemyBase::Death()
{
	bDead = true;
	auto Player = Cast<AC_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
		Player->AddExp(Exp);
	DropItem();
	EndDamaged();
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AnimInstance->Death();
	FTimerHandle TimeHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, [this]() {this->Destroy(); }, 6.0f, false);
}

