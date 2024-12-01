// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionTypes.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include "C_EnemyHumanoidAI.generated.h"


class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class VJLINK_API AC_EnemyHumanoidAI : public AAIController
{
	GENERATED_BODY()
public:
	AC_EnemyHumanoidAI();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Sight* SightCfg;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimuliSource();

	UFUNCTION()
	void OnTargetSniffed(AActor* SniffedActor, FAIStimulus const Stimulus);

	
};
