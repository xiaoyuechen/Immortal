// Copyright J&J

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolPointsComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ensure(ControlledPawn)){ return EBTNodeResult::Failed; }
	auto PatrolPointsComponent = ControlledPawn->FindComponentByClass<UPatrolPointsComponent>();
	if(!ensure(PatrolPointsComponent)){ return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolPointsComponent->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol points"), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!ensure(BlackboardComp)) { return EBTNodeResult::Failed; }
	auto Index = BlackboardComp->GetValueAsInt(WaypointIndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	UE_LOG(LogTemp, Warning, TEXT("Index Num: %d"), Index);

	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(WaypointIndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;

}


