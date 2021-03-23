// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackSkillBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "C_Player.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
AAttackSkillBase::AAttackSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);

	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");

}

// Called when the game starts or when spawned
void AAttackSkillBase::BeginPlay()
{
	Super::BeginPlay();

	if (LifeTime > 0)
	{
		FTimerHandle TimeHandle;
		GetWorld()->GetTimerManager().SetTimer(TimeHandle, [this]() { this->Destroy(); }, LifeTime, false);
	}
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AAttackSkillBase::Tick(float DeltaTime)
{

}

void AAttackSkillBase::BeginOverlap(UPrimitiveComponent* OverComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AAttackSkillBase::ActiveBoxDamage()
{
	if (Damage == 0)
		return;
	UE_LOG(LogTemp, Warning, TEXT("%f"), Damage);
	TArray<FOverlapResult> Hits;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FName CollisionName = bPlayerSkill ? "PSkill" : "ESKill";

	GetWorld()->OverlapMultiByProfile
	(
		Hits,
		Collision->GetComponentLocation(),
		FQuat::Identity,
		CollisionName,
		Collision->GetCollisionShape(),
		CollisionQueryParam
	);

	for (FOverlapResult hit : Hits)
	{
		UGameplayStatics::ApplyDamage(hit.GetActor(), Damage * DamageFactors, NULL, this, NULL);
	}
}

