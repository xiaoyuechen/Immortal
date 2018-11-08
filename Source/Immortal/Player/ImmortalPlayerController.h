// Copyright J&J.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ImmortalPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerControllerDelegate);


/**
 * This class is the player controller class for Immortal. 
 * It is Responsible for swapping characters (player's persist ability) and controlling UI.
 */

UCLASS()
class IMMORTAL_API AImmortalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AImmortalPlayerController();
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Swap")
	void SwapCharacter();

	FPlayerControllerDelegate OnSwap;

protected:
	virtual void SetupInputComponent() override;
	virtual void QuitGame();

	void OnCharacter0Death();
	void OnOtherCharacterDeadth();
	void AimTowardsCrossHead();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

private:
	UFUNCTION()
	void OnCharacterDeath();

	/** Returns the closest pawn other than possessed pawn within the swap radius */
	APawn* GetClosestPawn();

	class AImmortalCharacter* PossessedCharacter;

	class UClass* Character0Blueprint;

	class UParabolicWeaponControllerComponent* FireComponent;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float SwapRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float LineTraceRange = 1000000.f;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float CrosshairYLocation = 0.33333f;
};
