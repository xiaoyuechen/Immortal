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
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	UClass* ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	int32 ProjectileNumber = 9999999;

	// The minimal interval between two projectile fires, in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	float WeaponCoolingTime = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	float LaunchSpeed = 1000.f;

	FTimerHandle Timer;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Fire();
	
	EFiringState GetFiringState() const;
};
