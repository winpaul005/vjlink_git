// Fill out your copyright notice in the Description page of Project Settings.

#include "C_EnemyHumanoidBTTask_Chase.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include <vjlink/C_PlayerCharacter.h>

UC_EnemyHumanoidBTTask_Chase::UC_EnemyHumanoidBTTask_Chase()
{
	NodeName = TEXT("Chase Player");
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UC_EnemyHumanoidBTTask_Chase, BlackboardKey));

}

EBTNodeResult::Type UC_EnemyHumanoidBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location;
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* Pawn = AIController->GetPawn();
	const FVector CurrentLocation = Pawn->GetActorLocation();
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	AActor* TargetPlayer = (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(NavSys) && IsValid(TargetPlayer))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, TargetPlayer->GetActorLocation());
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;



}

FString UC_EnemyHumanoidBTTask_Chase::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
