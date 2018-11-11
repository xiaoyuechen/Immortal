// CopyRight J&J

#include "ParabolicWeaponControllerComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


UParabolicWeaponControllerComponent::UParabolicWeaponControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Set default projectile blueprint
	static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprintFinder(TEXT("Class'/Game/Immortal/Weapons/Projectiles/Projectile0/BP_Projectile0.BP_Projectile0_C'"));
	if (ProjectileBlueprintFinder.Succeeded())
	{
		ProjectileBlueprint = ProjectileBlueprintFinder.Object;
	}

}

void UParabolicWeaponControllerComponent::Initialise(USceneComponent * MuzzleToSet, UStaticMeshComponent* GunToSet)
{
	Muzzle = MuzzleToSet;
	Gun = GunToSet;
}

// Called when the game starts
void UParabolicWeaponControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	FiringState = EFiringState::Ready;

}



// Called every frame
void UParabolicWeaponControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

void UParabolicWeaponControllerComponent::AimAt(FVector Location)
{
	if (!ensure(Gun && ProjectileBlueprint)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Gun->GetComponentLocation();

	auto ProjectileBlueprintObj = NewObject<AProjectile>(this, ProjectileBlueprint);
	if (!ProjectileBlueprintObj) { return; }
	if (!ProjectileBlueprintObj->GetProjectileMovementComponent()) { return; }
	float GravityZ = ProjectileBlueprintObj->GetProjectileMovementComponent()->GetGravityZ();
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, Location, LaunchSpeed, false, 0, GravityZ, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		RotateGunTowardsDirection(AimDirection);
	}
}

void UParabolicWeaponControllerComponent::RotateGunTowardsDirection(FVector Direction)
{
	Gun->SetWorldRotation(Direction.Rotation());
}

void UParabolicWeaponControllerComponent::RotateGunTowardsLocation(FVector Location)
{
	FVector AimDirection = Location - Gun->GetComponentLocation();
	RotateGunTowardsDirection(AimDirection);
}

void UParabolicWeaponControllerComponent::Fire()
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

		auto Projectile = GetWorld()-> SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation, ActorSpawnParams);

		if (!Projectile)
		{ 
			UE_LOG(LogTemp, Warning, TEXT("Spawning projectile failed"));
			return; 
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		GetWorld()->GetTimerManager().SetTimer(Timer, WeaponCoolingTime, false);

		// try and play the sound if specified
		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, SpawnLocation);
		}
	}
}

EFiringState UParabolicWeaponControllerComponent::GetFiringState() const
{
	return FiringState;
}

