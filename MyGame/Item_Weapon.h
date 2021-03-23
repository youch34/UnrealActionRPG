// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AItem_Weapon : public AItem
{
	GENERATED_BODY()
	
public:
	void Equip(class AC_Player* player);

	void UnEquip(class AC_Player* player);

	virtual void Use(class AC_Player* player) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		bool bEquiped = false;
private:
};
