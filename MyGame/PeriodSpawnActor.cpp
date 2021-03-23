// Fill out your copyright notice in the Description page of Project Settings.


#include "PeriodSpawnActor.h"
#include "Engine/World.h"

// Sets default values
APeriodSpawnActor::APeriodSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bEnd = false;
}

void APeriodSpawnActor::Init(float Xrange, float Yrange, float height)
{
	this->XRange = Xrange;
	this->YRange = Yrange;
	this->Height = height;
};
// Called when the game starts or when spawned
void APeriodSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	Timer = Period;
}

// Called every frame
void APeriodSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentNum >= SpawnNum)
	{
		Destroy();
		return;
	}
	Timer -= DeltaTime;
	if (Timer < 0)
	{
		SpawnActor();
		CurrentNum += 1;
		Timer = Period;
	}
}

void APeriodSpawnActor::SpawnActor()
{
	FVector Location;
	FVector ActorPos = GetActorLocation();
	float X = FMath::RandRange(ActorPos.X - XRange * 0.5f, ActorPos.X + XRange * 0.5f);
	float Y = FMath::RandRange(ActorPos.Y - YRange * 0.5f, ActorPos.Y + YRange * 0.5f);
	float Z = Height;
	Location.X = X;
	Location.Y = Y;
	Location.Z = Z;
	GetWorld()->SpawnActor<AActor>(Spawnactor, Location, GetActorRotation());
}

