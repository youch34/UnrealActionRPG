// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		bool AddItem(class AItem* item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(class AItem* item);
	UFUNCTION(BlueprintCallable)
		void Refresh();
	
	//시작할때 있을 기본아이템
	UPROPERTY(EditDefaultsOnly)
		TArray<class AItem*> DefaultItem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
		TMap<class AItem*, int> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
		FVector DummyPos = FVector(10000,10000,10000);
};
