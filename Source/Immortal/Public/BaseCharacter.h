// Copyright J&J.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseCharacterDelegate);

/**
* This class is the base character for Immortal, and it is responsible for all
* physical interaction between the player and the world.
*
* The capsule component (inherited from ACharacter) handles collision with the world
* The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
* The Sprite component (inherited from APaperCharacter) handles the visuals
*/

UCLASS(config = Game)
class ABaseCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* SideViewCameraComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	//class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called to update character graphics*/
	void UpdateCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	/** Called to fire */
	UFUNCTION(BlueprintCallable, Category = "CharacterActions")
		virtual void Fire();

	/** Called to move right */
	UFUNCTION(BlueprintCallable, Category = "CharacterActions")
		virtual void MoveRight(float Value);

	/** Called by the engined when actor damage is dealt */
	float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser
	) override;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
		int32 StartingHealth;

	UPROPERTY(VisibleAnywhere, Category = "CharacterSetup")
		int32 CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
		float Damage;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
		float DamageRadius;

public:


	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Reset")
		void ResetCharacter();


	FBaseCharacterDelegate OnDeath;

};
