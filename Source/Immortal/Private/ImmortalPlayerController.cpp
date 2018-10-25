// Fill out your copyright notice in the Description page of Project Settings.

#include "ImmortalPlayerController.h"

void AImmortalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	APaperCharacter* ControlledCharacter = GetControlledCharacter();
	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is not controlling any character."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is controlling %s."), *ControlledCharacter->GetName());
	}
}


APaperCharacter* AImmortalPlayerController::GetControlledCharacter() const
{
	return Cast<APaperCharacter>(GetPawn());
}

