// CopyRight J&J

#include "BaseFireComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseProjectile.h"


// Sets default values for this component's properties
UBaseFireComponent::UBaseFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ProjectileBlueprintObj(TEXT("/Game/Immortal/Weapons/BaseProjectile/BP_BaseProjectile"));
	if (ProjectileBlueprintObj.Succeeded())
	{
		ProjectileBlueprint = ProjectileBlueprintObj.Object->GeneratedClass;
	}

	ProjectileNumber = 999999;
	WeaponCoolingTime = 1.f;
	LaunchSpeed = 1000;
}


// Called when the game starts
void UBaseFireComponent::BeginPlay()
{
	Super::BeginPlay();

	FiringState = EFiringState::Ready;
	
}


// Called every frame
void UBaseFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ProjectileNumber <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if (GetWorld()->GetTimerManager().GetTimerElapsed(Timer) > WeaponCoolingTime)
	{
		FiringState = EFiringState::Cooling;
	}
	else
	{
		FiringState = EFiringState::Ready;
	}

}

void UBaseFireComponent::Fire()
{
	if (!ensure(ProjectileBlueprint)) { return; }

	if (FiringState == EFiringState::Ready)
	{
		FVector OwnerLocation = GetOwner()->GetActorLocation();
		FVector SpawnLocation = FVector(OwnerLocation.X, OwnerLocation.Y, OwnerLocation.Z + 150.f);
		auto Projectile = GetWorld()->
			SpawnActor<ABaseProjectile>
			(
				ProjectileBlueprint,
				SpawnLocation,
				GetOwner()->GetActorRotation()
			);
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

