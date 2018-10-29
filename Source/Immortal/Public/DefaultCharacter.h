// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "DefaultCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDefaultCharacterDelegate);

/**
 * This class is the default character for Immortal, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
class USphereComponent;

UCLASS(config = Game)
class ADefaultCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ADefaultCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;


	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	void UpdateCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	// End of APawn interface


	/** Called to fire*/
	UFUNCTION(BlueprintCallable, Category = "CharacterActions")
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = "CharacterActions")
	virtual void MoveRight(float Value);

public:

	/** Called by the engined when actor damage is dealt */
	float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	void ResetCharacter();

	FDefaultCharacterDelegate OnDeath;

private:
	UPROPERTY(EditAnywhere, Category = CharacterSetup)
	int32 StartingHealth;

	UPROPERTY(VisibleAnywhere, Category = CharacterSetup)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, Category = CharacterSetup)
	float Damage;

	UPROPERTY(EditAnywhere, Category = CharacterSetup)
	float DamageRadius;

};
