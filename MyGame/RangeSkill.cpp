// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeSkill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
ARangeSkill::ARangeSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActiveEnd = false;
}

// Called when the game starts or when spawned
void ARangeSkill::BeginPlay()
{
	Super::BeginPlay();
	FMath::Clamp<float>(ActiveTimeRate, 0.0f, 1.0f);
}

// Called every frame
void ARangeSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveEnd == true)
		return;
	CurrentTIme += DeltaTime;

	if (CurrentTIme >= ActiveTimeRate * LifeTime)
	{
		if (ExplosionSound)
		{
			Audio->SetSound(ExplosionSound);
			Audio->Play();
		}
		ActiveBoxDamage();
		ActiveEnd = true;
	}
}


