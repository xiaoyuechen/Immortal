// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Characters/ImmortalCharacter.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetParentCharacter(AImmortalCharacter* NewParentCharacter);

	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;

protected:
	UPROPERTY(VisibleAnywhere)
	AImmortalCharacter* ParentCharacter;
	
	
};
