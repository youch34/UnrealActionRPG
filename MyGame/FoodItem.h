// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "FoodItem.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API AFoodItem : public AItem
{
	GENERATED_BODY()

protected:
	virtual void Use(class AC_Player* Player) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float AddHp;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		TSubclassOf<class AActor> UseEffect;
};