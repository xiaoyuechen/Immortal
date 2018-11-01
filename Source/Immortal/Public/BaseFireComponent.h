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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	TSubclassOf<ABaseProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	int32 ProjectileNumber;

	// the minimal interval between two projectile fires, in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	float WeaponCoolingTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	float LaunchSpeed;

	FTimerHandle Timer;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Fire();
	
};
