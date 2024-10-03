// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyHumanoidBTTask_Patrol.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
UC_EnemyHumanoidBTTask_Patrol::UC_EnemyHumanoidBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UC_EnemyHumanoidBTTask_Patrol, BlackboardKey));
}

EBTNodeResult::Type UC_EnemyHumanoidBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location;
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* Pawn = AIController->GetPawn();
	const FVector CurrentLocation = Pawn->GetActorLocation();
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (IsValid(NavSys) && NavSys->GetRandomPointInNavigableRadius(CurrentLocation, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UC_EnemyHumanoidBTTask_Patrol::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
