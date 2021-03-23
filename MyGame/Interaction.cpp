// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction.h"
#include "C_Player.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AInteraction::AInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Collision = CreateDefaultSubobject<USphereComponent>("Collsion");
	Collision->AttachTo(Mesh);
}

void AInteraction::BeginPlay()
{
	Super::BeginPlay();
}

void AInteraction::Action(AC_Player* player)
{

}
