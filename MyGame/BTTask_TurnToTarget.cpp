// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "C_EnemyAIController.h"
#include "C_Player.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	auto Target = Cast<AC_Player>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AC_EnemyAIController::TargetKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ControllingPawn->SetActorRotation(
		FMath::RInterpTo(ControllingPawn->GetActorRotation(),TargetRot , GetWorld()->GetDeltaSeconds(), TurnSpeed
		));

	return EBTNodeResult::Succeeded;
}