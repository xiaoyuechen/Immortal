// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ImmortalPlayerController.generated.h"

/**
 * 
 */
class ABaseCharacter;

UCLASS()
class IMMORTAL_API AImmortalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Swap")
	void SwapCharacter();

protected:
	virtual void SetupInputComponent() override;


private:
	UFUNCTION()
	void OnCharacterDeath();

	/** Returns the closest pawn other than possessed pawn within the swap radius */
	APawn* GetClosestPawn();

	ABaseCharacter* ControlledCharacter = nullptr;

	UPROPERTY(EditAnywhere, Category = CharacterSetup)
	float SwapRadius = 200;

};
