// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

void UHealthBarWidget::SetParentCharacter(class AImmortalCharacter* NewParentCharacter)
{
	ParentCharacter	= NewParentCharacter;
}

float UHealthBarWidget::GetHealthPercent() const
{
	if (!ParentCharacter) { return 0.f; }
	return ParentCharacter->GetHealthPercent();
}