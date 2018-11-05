// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseHealthBarWidgetComponent.generated.h"

/**
 * This class is responsible for drawing health bar widget. 
 * You can add this class as a health bar widget component to a character.
 * You can also choose which health bar widget to draw by assigning it in blueprint
 */
UCLASS(ClassGroup = (UserInterface), meta = (BlueprintSpawnableComponent))
class IMMORTAL_API UBaseHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UBaseHealthBarWidgetComponent();

	virtual void BeginPlay() override;
};
