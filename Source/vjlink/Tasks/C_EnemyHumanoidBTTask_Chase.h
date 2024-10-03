

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_EnemyHumanoidBTTask_Chase.generated.h"

/**
 *
 */
UCLASS()
class VJLINK_API UC_EnemyHumanoidBTTask_Chase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UC_EnemyHumanoidBTTask_Chase();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 1400.0f;


};