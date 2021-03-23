// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PeriodSpawnActor.generated.h"

UCLASS()
class MYGAME_API APeriodSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeriodSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Init(float Xrange, float Yrange, float height);
	void SpawnActor();
	bool IsEnd() { return bEnd; }
	void Destory() { Destroy(); }
	float GetCastTime() { return Period * SpawnNum; }
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> Spawnactor;
	UPROPERTY(EditDefaultsOnly)
		float Period;
	float Timer;
	UPROPERTY(EditDefaultsOnly)
		int SpawnNum;
	int CurrentNum;
	bool bEnd;
private:
	float XRange;
	float YRange;
	float Height;
};
