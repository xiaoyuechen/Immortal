// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultCharacter.h"
#include "ImmortalPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_API AImmortalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APaperCharacter* GetControlledCharacter() const;
	
	void BeginPlay() override;
	
};
