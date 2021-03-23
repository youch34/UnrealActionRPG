// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "C_Player.h"

TArray<APortal*> APortal::portals;

APortal::APortal() 
{
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	portals.Add(this);
}

void APortal::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	portals.Empty();
}

void APortal::Action(AC_Player* player)
{
	FVector goal = {0,0,0};
	for (auto portal : portals)
	{
		if (portal->Number == GoalPortalNum)
			goal = portal->GetActorLocation();
	}
	player->SetActorLocation(goal);
}
