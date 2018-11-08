// Copyright J&J

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolPointsComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto PatrolPointsComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolPointsComponent>();
	if(!ensure(PatrolPointsComponent)){ return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolPointsComponent->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol points"), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		return EBTNodeResult::Failed;
	}
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(WaypointIndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(WaypointIndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;

}