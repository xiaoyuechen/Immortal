// CopyRight J&J

#include "BaseFireComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseProjectile.h"

UBaseFireComponent::UBaseFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Set default projectile blueprint
	static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprintFinder
	(
		TEXT("Class'/Game/Immortal/Weapons/BaseProjectile/BP_BaseProjectile.BP_BaseProjectile_C'")
	);
	if (ProjectileBlueprintFinder.Succeeded())
	{
		ProjectileBlueprint = ProjectileBlueprintFinder.Object;
	}
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
	else if (GetWorld()->GetTimerManager().GetTimerRate(Timer) > 0)
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
		FVector SpawnLocation = FVector(OwnerLocation.X, OwnerLocation.Y, OwnerLocation.Z + 110.f);
		auto Projectile = GetWorld()->
			SpawnActor<ABaseProjectile>
			(
				ProjectileBlueprint,
				SpawnLocation,
				GetOwner()->GetActorRotation()
			);
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		GetWorld()->GetTimerManager().SetTimer(Timer,WeaponCoolingTime,false);
	}
}

EFiringState UBaseFireComponent::GetFiringState() const
{
	return FiringState;
}

