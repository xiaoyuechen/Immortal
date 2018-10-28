// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultCharacter.h"
#include "AIController.h"
#include "Character1AIController.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_API ACharacter1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	ADefaultCharacter* GetControlledCharacter() const;

	ADefaultCharacter* GetPlayerCharacter() const;

	virtual void SetPawn(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnCharacterDeath();
};
