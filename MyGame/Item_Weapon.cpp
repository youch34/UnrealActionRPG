// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Weapon.h"
#include "InventoryComponent.h"
#include "C_Player.h"
#include "Components/SkeletalMeshComponent.h"

void AItem_Weapon::Equip(AC_Player* player) 
{
	bEquiped = true;
	if (player->GetCurWeapon())
	{
		player->GetCurWeapon()->UnEquip(player);
	}
	player->SetCurWeapon(this);
}
void AItem_Weapon::UnEquip(AC_Player* player)
{
	bEquiped = false;
	player->SetCurWeapon(nullptr);
}

void AItem_Weapon::Use(AC_Player* player)
{
	if (bEquiped == false)
		Equip(player);
	else
		UnEquip(player);
}


