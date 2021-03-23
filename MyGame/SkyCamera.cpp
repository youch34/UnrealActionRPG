// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyCamera.h"

#include "C_Player.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
ASkyCamera::ASkyCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> rtv
	(
		TEXT("TextureRenderTarget2D'/Game/Texture/RTV_SkyVIew.RTV_SkyVIew'")
	);
	if (rtv.Succeeded())
		RTV = rtv.Object;

	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>("Camera");
	Camera->TextureTarget = RTV;
}

// Called when the game starts or when spawned
void ASkyCamera::BeginPlay()
{
	Super::BeginPlay();
	Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Camera->SetRelativeRotation(FRotator(-90, 0, 0));
}

// Called every frame
void ASkyCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Target) 
	{
		FVector Pos = Target->GetActorLocation();
		Pos.Z += Height;
		SetActorLocation(Pos);
	}
}

