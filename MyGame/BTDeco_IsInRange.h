// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDeco_IsInRange.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UBTDeco_IsInRange : public UBTDecorator
{
	GENERATED_BODY()

public:
    bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
