// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"
#include "Engine/World.h"
#include "C_Player.h"
#include "InventoryComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

void AFoodItem::Use(AC_Player* Player)
{
	if (Player)
	{
		if (Player->Hp >= Player->MaxHp)
			return;
		if (UseEffect)
			GetWorld()->SpawnActor<AActor>(UseEffect,Player->GetActorLocation(),Player->GetActorRotation());

		if (Player->Audio && Player->HealSound)
		{
			Player->Audio->SetSound(Player->HealSound);
			Player->Audio->Play(); 
		}
		Player->Hp += AddHp;
		OwningInventory->RemoveItem(this);
	}
}