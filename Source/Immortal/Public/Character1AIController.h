// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character1AIController.generated.h"

/**
 * 
 */
class ABaseCharacter;

UCLASS()
class IMMORTAL_API ACharacter1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	ABaseCharacter* GetControlledCharacter() const;

	ABaseCharacter* GetPlayerCharacter() const;

	virtual void SetPawn(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnCharacterDeath();
};
