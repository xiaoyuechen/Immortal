// CopyRight J&J

#include "BaseFireComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


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
	if (!ensure(Gun && Muzzle && ProjectileBlueprint)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Muzzle->GetComponentLocation();
	
	auto ProjectileBlueprintObj = NewObject<ABaseProjectile>(this, ProjectileBlueprint);
	if (!ProjectileBlueprintObj) { return; }
	if (!ProjectileBlueprintObj->GetProjectileMovementComponent()) { return; }
	float GravityZ = ProjectileBlueprintObj->GetProjectileMovementComponent()->GetGravityZ();
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		Location,
		LaunchSpeed,
		false,
		0,
		GravityZ,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		RotateGunTowardsDirection(AimDirection);
	}
}

void UBaseFireComponent::RotateGunTowardsDirection(FVector Direction)
{
	FRotator CorrectRotator(Gun->GetComponentRotation().Pitch, Gun->GetComponentRotation().Yaw, -Direction.Rotation().Pitch);
	UE_LOG(LogTemp, Warning, TEXT("GunRotator: %s"), *Direction.Rotation().ToString());
	Gun->SetWorldRotation(CorrectRotator);
}

void UBaseFireComponent::RotateGunTowardsLocation(FVector Location)
{
	FVector AimDirection = Location - Muzzle->GetComponentLocation();
	RotateGunTowardsDirection(AimDirection);
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

