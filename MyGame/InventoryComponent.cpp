// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Item.h"
#include "FoodItem.h"
// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 20;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool UInventoryComponent::AddItem(class AItem* item)
{
	if (!item || Items.Num() >= Capacity)
		return false;

	//이미 존재하는 아이템인경우
	for (auto _item : Items)
	{
		if (_item.Key->ItemCode == item->ItemCode)
		{
			Items[_item.Key]++;
			item->Destroy();
			return true;
		}
	}
	//새로 추가된경우
	item->OwningInventory = this;
	Items.Add(item, 1);
	OnInventoryUpdated.Broadcast();
	Refresh();
	return true;
}

bool UInventoryComponent::RemoveItem(class AItem* item)
{
	if (item)
	{
		for (auto _item : Items)
		{
			if (_item.Key->ItemCode == item->ItemCode)
			{
				if (_item.Value > 1)
				{
					Items[_item.Key]--;
				}
				else 
				{
					UE_LOG(LogTemp, Warning, TEXT("%x have removed"), _item.Key);
					Items.Remove(_item.Key);
					_item.Key->Destroy();
				}
				break;
			}
		}
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

void UInventoryComponent::Refresh()
{
	for (auto item : Items)
	{
		item.Key->SetActorLocation(DummyPos);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *item.Key->GetName());
	}
}



