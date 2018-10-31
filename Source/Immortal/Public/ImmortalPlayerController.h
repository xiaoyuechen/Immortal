// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ImmortalPlayerController.generated.h"

/**
 * This class is the player controller class for Immortal. 
 * It is Responsible for swapping characters (player's persist ability) and controlling UI.
 */

UCLASS()
class IMMORTAL_API AImmortalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Swap")
	void SwapCharacter();

protected:
	virtual void SetupInputComponent() override;
	virtual void QuitGame();


private:
	UFUNCTION()
	void OnCharacterDeath();

	/** Returns the closest pawn other than possessed pawn within the swap radius */
	APawn* GetClosestPawn();

	class ABaseCharacter* ControlledCharacter = nullptr;

	UPROPERTY(EditAnywhere, Category = CharacterSetup)
	float SwapRadius = 200;

};
