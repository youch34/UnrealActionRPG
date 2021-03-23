// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSkill.h"
#include "Engine/World.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "C_Player.h"
#include "C_EnemyBase.h"
// Sets default values
AProjectileSkill::AProjectileSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

}

// Called when the game starts or when spawned
void AProjectileSkill::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileSkill::BeginOverlap);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called every frame
void AProjectileSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileSkill::BeginOverlap(UPrimitiveComponent* OverComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bExplosion == false)
		return;
	
	if (OverComp && OtherActor && OtherActor != this)
	{
		if (ExplosionParticle)
			GetWorld()->SpawnActor<AActor>(ExplosionParticle, GetTransform());
		ActiveBoxDamage();
		Destroy();
		return;
	}
}

