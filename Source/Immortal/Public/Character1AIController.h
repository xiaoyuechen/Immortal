// Copyright J&J.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character1AIController.generated.h"

/**
 * This class is character1 AI controller for immortal.
 * It can move character1 back and forth, detect the player character, 
 * and move towards it until an acceptance range. 
 * It also fires at the player character. 
 */

UCLASS()
class IMMORTAL_API ACharacter1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACharacter1AIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	class ABaseCharacter* GetPlayerCharacter() const;

	virtual void SetPawn(APawn* InPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float DetectRadius = 500;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MovementDirectionMod = 0.8f;

	UFUNCTION()
	virtual void OnCharacterDeath();

	UFUNCTION()
	virtual	void OnHit
	(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	ABaseCharacter* PossessedCharacter;
	ABaseCharacter* PlayerCharacter;
};
