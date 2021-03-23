// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDisplay.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADamageDisplay::ADamageDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetWorldSize(100);
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Text->SetTextRenderColor(FColor::Red);

}

// Called when the game starts or when spawned
void ADamageDisplay::BeginPlay()
{
	Super::BeginPlay();
}

void ADamageDisplay::SetString(FString str)
{
}

void ADamageDisplay::SetRotation()
{
	auto CM = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);
	FVector vec = CM->GetCameraLocation() - GetActorLocation();
	FRotator rot = vec.Rotation();
	SetActorRotation(rot);
}

// Called every frame
void ADamageDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector temp = GetActorLocation();
	temp.Z += DeltaTime * 100;
	SetActorLocation(temp);
	SetRotation();
	curtime += DeltaTime;
	if (curtime > lifetime)
		Destroy();
}

