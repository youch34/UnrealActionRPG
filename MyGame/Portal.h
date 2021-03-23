// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction.h"
#include "Portal.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API APortal : public AInteraction
{
	GENERATED_BODY()
public:
	APortal();

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void Action(class AC_Player* player) override;

	static TArray<APortal*> portals;

	UPROPERTY(EditInstanceOnly)
		int32 Number;

	UPROPERTY(EditInstanceOnly)
		int32 GoalPortalNum;
};
