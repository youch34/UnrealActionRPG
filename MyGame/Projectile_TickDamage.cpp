// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_TickDamage.h"

AProjectile_TickDamage::AProjectile_TickDamage() 
{
	CurrentTime = 0;
}

void AProjectile_TickDamage::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile_TickDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bStarted == false)
	{
		ActiveBoxDamage();
		bStarted = true;
	}
	CurrentTime += DeltaTime;
	if (CurrentTime >= TickTime)
	{
		ActiveBoxDamage();
		CurrentTime = 0;
	}
}

