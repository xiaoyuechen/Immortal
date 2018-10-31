// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseHealthBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (UserInterface), meta = (BlueprintSpawnableComponent))
class IMMORTAL_API UBaseHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UBaseHealthBarWidgetComponent();

	virtual void BeginPlay() override;
};
