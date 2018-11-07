// CopyRight J&J

#include "BaseFireComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


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

void UBaseFireComponent::Initialise(USceneComponent * MuzzleToSet, UStaticMeshComponent* GunToSet)
{
	Muzzle = MuzzleToSet;
	Gun = GunToSet;
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

void UBaseFireComponent::AimAt(FVector Location)
{
	if (!ensure(Gun) || !ensure(Muzzle)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Muzzle->GetComponentLocation();
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		Location,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveGunTowards(AimDirection);
}

void UBaseFireComponent::MoveGunTowards(FVector Direction)
{

	Gun->SetWorldRotation(Direction.Rotation());
}

void UBaseFireComponent::Fire()
{
	if (!ensure(ProjectileBlueprint)) { return; }

	if (FiringState == EFiringState::Ready)
	{
		if (!ensure(Muzzle)) { return; }
		FVector SpawnLocation = Muzzle->GetComponentLocation();
		FRotator SpawnRotation = Muzzle->GetComponentRotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		auto Projectile = GetWorld()->
			SpawnActor<ABaseProjectile>
			(
				ProjectileBlueprint,
				SpawnLocation,
				SpawnRotation,
				ActorSpawnParams
			);

		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		GetWorld()->GetTimerManager().SetTimer(Timer,WeaponCoolingTime,false);

		// try and play the sound if specified
		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, SpawnLocation);
		}
	}
}

EFiringState UBaseFireComponent::GetFiringState() const
{
	return FiringState;
}

