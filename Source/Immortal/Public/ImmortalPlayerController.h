// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ImmortalPlayerController.generated.h"

/**
 * 
 */
class ADefaultCharacter;
class UCharacterMovementComponent;

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


	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void Initialise(ADefaultCharacter* CharacterRef);
protected:
	virtual void SetupInputComponent() override;


private:
	UFUNCTION()
	void OnCharacterDeath();

	ADefaultCharacter* ControlledCharacter;

	UCharacterMovementComponent* MovementComponent;


};
