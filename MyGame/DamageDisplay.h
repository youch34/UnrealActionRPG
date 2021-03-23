// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageDisplay.generated.h"

UCLASS()
class MYGAME_API ADamageDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	void SetString(FString str);
	void SetRotation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	class UTextRenderComponent* Text;
	float curtime = 0.0f;
	float lifetime = 2.0f;
};
