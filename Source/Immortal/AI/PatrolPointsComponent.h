// Copyright J&J

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TargetPoint.h"
#include "PatrolPointsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_API UPatrolPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FORCEINLINE TArray<ATargetPoint*> GetPatrolPoints() const { return PatrolPoints; }

protected:

	UPROPERTY(EditInstanceOnly, Category = Setup)
	TArray<ATargetPoint*> PatrolPoints;

	
};
