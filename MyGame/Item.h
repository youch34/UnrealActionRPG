// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API AItem : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	AItem();

	//UPROPERTY()
	//	class UWorld* World;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		float ItemCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText UseActionText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
		class USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText PickUpText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
		float Weight;

	UPROPERTY()
		class UInventoryComponent* OwningInventory;


public:
	//virtual class UWorld* GetWorld() const { return World; }

	virtual void Use(class AC_Player* Player) {}

	UFUNCTION(BlueprintImplementableEvent, Blueprintcallable) //함수의 본문을 블루프린트에서 작성하겠다
		void OnUse(class AC_Player* Player);

	UFUNCTION(BlueprintImplementableEvent, Blueprintcallable)
		void ShowDisplayText();
};