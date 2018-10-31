// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHealthBarWidget.h"

void UBaseHealthBarWidget::SetParentCharacter(class ABaseCharacter* InCharacter)
{
	ParentCharacter	= InCharacter;
	UE_LOG(LogTemp, Warning, TEXT("Parent Character: %s"), *ParentCharacter->GetName());
}

float UBaseHealthBarWidget::GetHealthPercent() const
{
	if (!ParentCharacter) { return 0.f; }
	return ParentCharacter->GetHealthPercent();
}
