// Copyright J&J.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseCharacterDelegate);

UENUM()
enum class EActionState : uint8
{
	Idling,
	Walking,
	Jumping,
	Firing,
};

/**
* This class is the base character for Immortal, and it is responsible for all
* physical interaction between the player and the world.
*
* The capsule component (inherited from ACharacter) handles collision with the world
* The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
* The Sprite component (inherited from APaperCharacter) handles the visuals
*/

UCLASS(config = Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Called to fire */
	UFUNCTION(BlueprintCallable, Category = "CharacterActions")
	virtual void Fire();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called to move right */
	UFUNCTION(BlueprintCallable, Category = "CharacterActions")
	virtual void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


	/** Called by the engined when actor damage is dealt */
	float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser
	) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	int32 StartingHealth = 10;

	UPROPERTY(VisibleAnywhere, Category = "CharacterSetup")
	int32 CurrentHealth;

	// Disable movement when firing
	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	bool bFireMovementFreeze = true;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float FireMovementFreezeTime = 0.1f;

	FTimerHandle FireMovementFreezeTimer;

public:



	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Reset")
	void ResetCharacter();

	virtual bool IsFrozen();

	FBaseCharacterDelegate OnDeath;

};
