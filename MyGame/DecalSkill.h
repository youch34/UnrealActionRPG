// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DecalSkill.generated.h"

UCLASS()
class MYGAME_API ADecalSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
		class UMaterial* Mat;
	UPROPERTY(VisibleAnywhere)
		UDecalComponent* Circum;
	UPROPERTY(VisibleAnywhere)
		UDecalComponent* Area;
	class UMaterialInstanceDynamic* Circle_Instacne;
	class UMaterialInstanceDynamic* Area_Instacne;

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> SkillParticle;
public:
	UPROPERTY(EditDefaultsOnly)
		float CastingTime;
};
