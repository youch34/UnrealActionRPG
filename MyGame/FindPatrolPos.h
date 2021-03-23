// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindPatrolPos.generated.h"

UCLASS()
class MYGAME_API UFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindPatrolPos();
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

};
