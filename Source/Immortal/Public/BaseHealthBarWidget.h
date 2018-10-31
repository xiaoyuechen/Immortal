// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseCharacter.h"
#include "BaseHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_API UBaseHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetParentCharacter(ABaseCharacter* InCharacter);

	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;

protected:
	UPROPERTY(VisibleAnywhere)
	ABaseCharacter* ParentCharacter;
	
	
};
