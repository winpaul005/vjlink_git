// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyHumanoidAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include <Perception/AIPerceptionComponent.h>


AC_EnemyHumanoidAI::AC_EnemyHumanoidAI()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	SetupPerceptionSystem();
}

void AC_EnemyHumanoidAI::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}

}

void AC_EnemyHumanoidAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

void AC_EnemyHumanoidAI::SetupStimuliSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void AC_EnemyHumanoidAI::SetupPerceptionSystem()
{
	SightCfg = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if(SightCfg)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Componenet")));
		SightCfg->SightRadius = MaxSightRange;
		SightCfg->LoseSightRadius = SightCfg->SightRadius + MaxOffsetLostSight;
		SightCfg->PeripheralVisionAngleDegrees = MaxPerepherialSightAngle;
		SightCfg->SetMaxAge(5.f);
		SightCfg->AutoSuccessRangeFromLastSeenLocation = MaxSightRange + MaxOffsetLostSight;
		SightCfg->DetectionByAffiliation.bDetectEnemies = true;
		SightCfg->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightCfg->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AC_EnemyHumanoidAI::OnTargetSniffed);
		GetPerceptionComponent()->ConfigureSense(*SightCfg);
	}

}

void AC_EnemyHumanoidAI::OnTargetSniffed(AActor* SniffedActor, FAIStimulus const Stimulus)
{
	BlackboardComponent->SetValueAsBool("IsNoticing", Stimulus.WasSuccessfullySensed());
	if (Stimulus.WasSuccessfullySensed())
	{
		if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
		{
			Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
	}
}
