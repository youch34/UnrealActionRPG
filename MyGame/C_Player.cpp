// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Player.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Json/Public/Json.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


#include "RangeSkill.h"

#include "C_AnimPlayer.h"

#include "C_EnemyMelee.h"
#include "Item.h"
#include "Item_Weapon.h"
#include "InventoryComponent.h"
#include "Interaction.h"

// Sets default values
AC_Player::AC_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentCombo = 1;
	bNextCombo = false;
	MaxCombo = 4;
	HitStateImmune = false;
	ATKPow = 40.0f;
	//Arm, Camera
	//Arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	//Arm->TargetArmLength = 600.0f;
	//Arm->bDoCollisionTest = false;
	//Arm->bUsePawnControlRotation = true;
	//
	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->AttachTo(Arm);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>("WeaponCollision");
	WeaponCollision->AttachTo(GetMesh());
	//Sound
	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");

	static ConstructorHelpers::FObjectFinder<USoundCue> levelupsound
	(
		TEXT("SoundCue'/Game/Sound/Cue_LevelUp.Cue_LevelUp'")
	);
	if (levelupsound.Succeeded())
		LevelupSound = levelupsound.Object;

	Skill1SpawnPoint = CreateDefaultSubobject<USceneComponent>("Skiil1SpawnPoint");
	Skill1SpawnPoint->AttachTo(GetMesh());
	Skill2SpawnPoint = CreateDefaultSubobject<USceneComponent>("Skiil2SpawnPoint");
	Skill2SpawnPoint->AttachTo(GetMesh());
	Skill3SpawnPoint = CreateDefaultSubobject<USceneComponent>("Skiil3SpawnPoint");
	Skill3SpawnPoint->AttachTo(GetMesh());

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->AttachTo(GetMesh());

	CurrentWeapon = nullptr;
	
	Jm.SetFileName("Player.json");
}

void AC_Player::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UC_AnimPlayer>(GetMesh()->GetAnimInstance());
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

// Called when the game starts or when spawned
void AC_Player::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < Mat_Bodys.Num(); i++)
	{
		Mat_BodyInstances.Add(UMaterialInstanceDynamic::Create(Mat_Bodys[i], this));
		GetMesh()->SetMaterial(i, Mat_BodyInstances[i]);
		Mat_BodyInstances[i]->SetVectorParameterValue("BaseColor", DefaultColor);
	}
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LoadPlayerInfo();

}

AItem_Weapon* AC_Player::GetCurWeapon()
{
	if (CurrentWeapon)
		return CurrentWeapon;
	return nullptr;
}

void AC_Player::SetCurWeapon(AItem_Weapon* weapon)
{
	CurrentWeapon = weapon;
	if (weapon)
		WeaponMesh->SetSkeletalMesh(weapon->MeshComp->SkeletalMesh);
	else
		WeaponMesh->SetSkeletalMesh(nullptr);
}

// Called every frame
void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalcSkillCool(DeltaTime);
}

// Called to bind functionality to input
void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AC_Player::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AC_Player::RunPressed);
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &AC_Player::MouseLeft);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AC_Player::Dash);
	PlayerInputComponent->BindAction("BackDash", IE_Pressed, this, &AC_Player::BackDash);

	PlayerInputComponent->BindAction("G", IE_Pressed, this, &AC_Player::Action);

	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &AC_Player::CounterAttack);
	PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &AC_Player::Skill1);
	PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &AC_Player::Skill2);
	PlayerInputComponent->BindAction("Skill3", IE_Pressed, this, &AC_Player::Skill3);

	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Player::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AC_Player::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AC_Player::LookUp);

}


void AC_Player::MoveRight(float val)
{
	if (bAttacking == true || bDamaged == true || AnimInstance->bDashing) return;

	FRotator ControllerYaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	FVector vec = FRotationMatrix(ControllerYaw).GetScaledAxis(EAxis::Y);
	AddMovementInput(vec, val);
}

void AC_Player::MoveForward(float val)
{
	if (bAttacking == true || bDamaged == true || AnimInstance->bDashing) return;

	FRotator ControllerYaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	FVector vec = FRotationMatrix(ControllerYaw).GetScaledAxis(EAxis::X);
	AddMovementInput(vec, val);
}

void AC_Player::Turn(float val)
{
	AddControllerYawInput(val);
}

void AC_Player::LookUp(float val)
{
	AddControllerPitchInput(val);
}

void AC_Player::RunPressed()
{
	if (bRunning == false)
	{
		bRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
	else 
	{
		bRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

void AC_Player::MouseLeft()
{
	if (!CurrentWeapon || bDamaged == true || AnimInstance->bDashing)
		return;
	if (CurrentCombo == MaxCombo)
		return;
	if (bAttacking == true)
	{
		bNextCombo = true;
		return;
	}
	bAttacking = true;
	if(AnimInstance != NULL)
		AnimInstance->Attack();
}

void AC_Player::ResetCombo()
{
	bAttacking = false;
	CurrentCombo = 1;
	bNextCombo = false;
}

void AC_Player::LookAt(FVector GoalVec)
{
	FVector XYGoalVec = FVector(GoalVec.X, GoalVec.Y, 0);
	FVector XYActorVec = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector Dir = XYGoalVec - XYActorVec;
	Dir.Normalize();
	FVector CapsuleForwrd = GetCapsuleComponent()->GetForwardVector();
	float Dot = FVector::DotProduct(CapsuleForwrd, Dir);
	float Radian = FMath::Acos(Dot);
	float Degree = FMath::RadiansToDegrees(Radian);
	FVector Cross = FVector::CrossProduct(CapsuleForwrd,Dir);
	if (Cross.Z < 0)
		Degree = -Degree;
	FRotator Rotator = FRotator(0, GetActorRotation().Yaw + Degree, 0);
	SetActorRotation(Rotator);
}

void AC_Player::UseItem(AItem* item)
{
	if (item)
	{
		item->Use(this);
		item->OnUse(this);
		ItemUsed.Broadcast();
	}
}

void AC_Player::Action()
{
	TArray<FOverlapResult> Hits;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByChannel
	(
		Hits,
		GetActorLocation(),
		FQuat::Identity,
		ECC_EngineTraceChannel3,
		GetCapsuleComponent()->GetCollisionShape(),
		CollisionQueryParam
	);
	for (FOverlapResult hit : Hits)
	{
		if (hit.Actor->IsA<AInteraction>())
		{
			Cast<AInteraction>(hit.Actor)->Action(this);
		}
		if (hit.Actor->IsA<AItem>())
		{
			Inventory->AddItem(Cast<AItem>(hit.Actor));
			if(PickUp)
			{
				Audio->SetSound(PickUp);
				Audio->Play();
			}
			return;
		}
	}
}

void AC_Player::BasicFrontAttack()
{
	TArray<FOverlapResult> Hits;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByProfile
	(
		Hits,
		WeaponCollision->GetComponentLocation(),
		FQuat::Identity,
		"PSkill",
		WeaponCollision->GetCollisionShape(),
		CollisionQueryParam
	);
	for (FOverlapResult hit : Hits)
	{
		UGameplayStatics::ApplyDamage(hit.GetActor(), ATKPow, NULL, this, NULL);
	}
}

void AC_Player::FourthAttack()
{
	FActorSpawnParameters Param;
	FVector Location = GetActorLocation();
	Location.Z -= 110;
	auto particle = GetWorld()->SpawnActor<AActor>(FourthAttackParticle, Location,GetActorRotation(), Param);
	if (auto Skill = Cast<AAttackSkillBase>(particle))
	{
		Skill->Damage = ATKPow;
	}
}

void AC_Player::Skill1()
{
	if (bAttacking || bDamaged || AnimInstance->bDashing)
		return;
	if (IsCoolTime(1) == false)
		return;
	SetHitStateImmune(true);
	bAttacking = true;
	AnimInstance->Skill1();
}

void AC_Player::Skill2()
{
	if (bAttacking || bDamaged || AnimInstance->bDashing)
		return;
	if (IsCoolTime(2) == false)
		return;
	SetHitStateImmune(true);
	bAttacking = true;
	AnimInstance->Skill2();
}

void AC_Player::Skill3()
{
	if (bAttacking || bDamaged || AnimInstance->bDashing)
		return;
	if (IsCoolTime(3) == false)
		return;
	SetHitStateImmune(true);
	bAttacking = true;
	AnimInstance->Skill3();
}

void AC_Player::CalcSkillCool(float deltaTime)
{
	for (int i = 0; i < 3; i++)
	{
		curSkillCool[i] -= deltaTime;
	}
}

bool AC_Player::IsCoolTime(int num)
{
	bool result = curSkillCool[num - 1] <= 0;
	if (result == true)
		curSkillCool[num - 1] = skillCool[num - 1];
	return result;
}

void AC_Player::OnEndAttack()
{
	bEvade = false;
	if (bNextCombo == true)
	{
		CurrentCombo += 1;
		bNextCombo = false;
		AnimInstance->Attack();
		AnimInstance->JumpToAttackMontageSection(CurrentCombo);
		return;
	}
	ResetCombo();
	SetHitStateImmune(false);
}

void AC_Player::Dash()
{
	ResetCombo();
	bDamaged = false;
	AnimInstance->Dash();
	EndDamage();
}

void AC_Player::BackDash()
{
	ResetCombo();
	bDamaged = false;
	AnimInstance->BackDash();
	EndDamage();
}

AC_EnemyMelee* AC_Player::CheckCounter()
{
	TArray<FOverlapResult> hits;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);

	GetWorld()->OverlapMultiByChannel
	(
		hits,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(300),
		CollisionQueryParam
	);

	for (auto hit : hits) 
	{
		if (hit.Actor->IsA<AC_EnemyMelee>())
		{
			AC_EnemyMelee* Enemy = Cast<AC_EnemyMelee>(hit.Actor);
			if (Enemy->bCounter)
				return Enemy;
		}
	}

	return nullptr;
}

void AC_Player::CounterAttack()
{
	if (bAttacking || AnimInstance->bDashing)
		return;
	bEvade = true;
	if (AC_EnemyMelee* Enemy = CheckCounter()) 
	{
		FTimerHandle TimerHandle;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() 
			{
				UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
			},0.2f,false);
		LookAt(Enemy->GetActorLocation());
		bAttacking = true;
		AnimInstance->CounterAttack();
	}
}


float AC_Player::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Result = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (AnimInstance->bDashing == true || bEvade == true)
		return Result;
	Hp -= Damage;
	SetMaterial(DamagedColor);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { SetMaterial(DefaultColor); }, 0.3, false);
	if (HitStateImmune == true)
		return Result;
	bDamaged = true;
	LookAt(DamageCauser->GetActorLocation());
	LaunchCharacter(GetCapsuleComponent()->GetForwardVector() * -200.0f, false, false);
	AnimInstance->Damaged();
	return Result;
}

void AC_Player::EndDamage()
{

}

void AC_Player::SetMaterial(FVector vec)
{
	for (int i = 0; i < Mat_Bodys.Num(); i++)
	{
		Mat_BodyInstances[i]->SetVectorParameterValue("BaseColor", vec);
	}
}

void AC_Player::AddExp(float val)
{
	CurExp += val;
	while(CurExp >= MaxExp) 
	{
		CurExp -= MaxExp;
		LevelUp();
	}
	SavePlayerInfo();
}

void AC_Player::LevelUp()
{
	Audio->SetSound(LevelupSound);
	Audio->Play();
	Level++;
	MaxExp = FMath::FloorToInt(MaxExp *= 1.3f);
	MaxHp = FMath::FloorToInt(MaxHp *= 1.5f);
	Hp = MaxHp;
	ATKPow = FMath::FloorToInt(ATKPow *= 1.3f);
	if (LevelUpEffect)
	{
		FVector Pos = GetActorLocation();
		Pos.Z -= 90;
		GetWorld()->SpawnActor<AActor>(LevelUpEffect, Pos, GetActorRotation());
	}
}

void AC_Player::PlayFootstepSound()
{
	TArray<FHitResult> Results;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	CollisionQueryParam.bReturnPhysicalMaterial = true;
	FVector Start = GetActorLocation();
	FVector End = Start;
	End.Z -= 150;
	GetWorld()->LineTraceMultiByChannel
	(
		Results,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		CollisionQueryParam
	);
	for (auto& result : Results)
	{
		auto Name = result.GetActor()->GetName();
		if (result.PhysMaterial.Get()->SurfaceType == EPhysicalSurface::SurfaceType1)
		{
			Audio->SetSound(GrassFootstep);
			Audio->Play();
			return;
		}
	}
	Audio->SetSound(DefaultFootstep);
	Audio->Play();
}

void AC_Player::SavePlayerInfo()
{
	FString jsonstr;
	TSharedRef<TJsonWriter<TCHAR>> JsonObj = TJsonWriterFactory<>::Create(&jsonstr);
	JsonObj->WriteObjectStart();
	JsonObj->WriteValue<float>("CurExp", CurExp);
	JsonObj->WriteValue<float>("MaxExp", MaxExp);
	JsonObj->WriteValue<float>("MaxHp", MaxHp);
	JsonObj->WriteValue<float>("Level", Level);
	JsonObj->WriteValue<float>("ATKPow", ATKPow);
	JsonObj->WriteObjectEnd();
	JsonObj->Close();
	Jm.SavaData(jsonstr);
}
void AC_Player::LoadPlayerInfo()
{
	TSharedPtr<FJsonObject> LoadObj = Jm.LoadData();
	CurExp = LoadObj->GetNumberField("CurExp");
	MaxExp = LoadObj->GetNumberField("MaxExp");
	MaxHp = LoadObj->GetNumberField("MaxHp");
	Level = LoadObj->GetNumberField("Level");
	ATKPow = LoadObj->GetNumberField("ATKPow");
}


