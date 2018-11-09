// Copyright J&J.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ImmortalAIController.generated.h"

/**
 * This class is character1 AI controller for immortal.
 * It can move character1 back and forth, detect the player character, 
 * and move towards it until an acceptance range. 
 * It also fires at the player character. 
 */

UCLASS()
class IMMORTAL_API AImmortalAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AImmortalAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	class AImmortalCharacter* GetPlayerCharacter() const;

	virtual void SetPawn(APawn* InPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float DetectRadius = 800.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AttackRadius = 800.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MovementDirectionMod = 1.f;

	UFUNCTION()
	virtual void OnCharacterDeath();

	virtual void OnPlayerSwap();

	UFUNCTION()
	virtual	void OnHit
	(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	virtual float NormalizeDirection(float DirX);

	AImmortalCharacter* PossessedCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	AImmortalCharacter* PlayerCharacter;
};
