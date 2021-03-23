// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	Weight = 1.0f;
	UseActionText = FText::FromString("Use");
	ItemDisplayName = FText::FromString("Item");

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>("root");
	SetRootComponent(root);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	MeshComp->AttachTo(root);

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->AttachTo(root);
	Collision->SetSphereRadius(200.0f);

	FString str = ItemDisplayName.ToString() + LINE_TERMINATOR + "Press 'G'";
	PickUpText = FText::FromString(str);
	
}


void AItem::BeginPlay() 
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}