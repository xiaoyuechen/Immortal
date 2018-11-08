// Copyright J&J

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RadialWeaponControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_API URadialWeaponControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadialWeaponControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Setup)
	float Damage = 3.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float DamageRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float WeaponCooldownTime = .2f;

	FTimerHandle CooldownTimer;

	bool bActuallyFired = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void Fire();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	bool bShouldDrawSphere = false;
};