// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyCamera.generated.h"

UCLASS()
class MYGAME_API ASkyCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkyCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneCaptureComponent2D* Camera;

	UPROPERTY(EditInstanceOnly, Category = "Target")
		class APawn* Target;
	UPROPERTY(EditDefaultsOnly)
		float Height;

	class UTextureRenderTarget2D* RTV;

};
