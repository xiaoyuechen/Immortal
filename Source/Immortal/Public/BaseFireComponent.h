// CopyRight J&J

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseFireComponent.generated.h"

class ABaseProjectile;

UENUM()
enum class EFiringState : uint8
{
	Ready,
	Cooling,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_API UBaseFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	EFiringState FiringState;

	// Decides which projectile to launch
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UClass* ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 ProjectileNumber = 9999999;

	// The minimal interval between two projectile fires, in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float WeaponCoolingTime = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LaunchSpeed = 1000.f;

	// At whose location projectiles are spawned
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* Muzzle;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = "Setup")
	class USoundBase* FireSound;

	FTimerHandle Timer;

	UFUNCTION(BlueprintCallable, Category = "WeaponSetup")
	void Initialise(USceneComponent* MuzzleToSet);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AimAt() {}

	virtual void Fire();
	
	EFiringState GetFiringState() const;
};
