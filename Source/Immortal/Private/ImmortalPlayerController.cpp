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


ADefaultCharacter* AImmortalPlayerController::GetControlledCharacter() const
{
	return Cast<ADefaultCharacter>(GetPawn());
}

void AImmortalPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto ControlledCharacter = Cast<ADefaultCharacter>(InPawn);
		if (!ensure(ControlledCharacter)) { return; }
		ControlledCharacter->OnDeath.AddUniqueDynamic(this, &AImmortalPlayerController::OnCharacterDeath);
	}
}

void AImmortalPlayerController::SwapCharacter()
{
	//auto ControlledCharacter = GetControlledCharacter();
	//if (!ensure(ControlledCharacter)) { return; }
	//TArray<AActor*> ActorsToSwap = ControlledCharacter->SwapRange->GetOverlappingActors();
}

void AImmortalPlayerController::OnCharacterDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Character Died"));
}



