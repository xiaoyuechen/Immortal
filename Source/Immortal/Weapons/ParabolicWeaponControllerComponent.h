// CopyRight J&J

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParabolicWeaponControllerComponent.generated.h"

class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Ready,
	Cooling,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_API UParabolicWeaponControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParabolicWeaponControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	EFiringState FiringState;

	// Decides which projectile to launch
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UClass* ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 ProjectileNumber = 9999999;

	// The minimal interval between two projectile fires, in seconds
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float WeaponCoolingTime = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float LaunchSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Gun;

	// At whose location projectiles are spawned
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* Muzzle;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	class USoundBase* FireSound;

	FTimerHandle Timer;

	FVector AimDirection;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Initialise(USceneComponent* MuzzleToSet, UStaticMeshComponent* GunToSet);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void RotateGunTowardsDirection(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void RotateGunTowardsLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void Fire();
	
	EFiringState GetFiringState() const;
};
