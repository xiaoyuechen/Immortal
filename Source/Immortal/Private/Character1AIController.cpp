// Fill out your copyright notice in the Description page of Project Settings.

#include "Character1AIController.h"
#include "Engine/World.h"
#include "BaseCharacter.h"

void ACharacter1AIController::BeginPlay()
{
	Super::BeginPlay();
	ABaseCharacter* ControlledCharacter = GetControlledCharacter();
	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller is not controlling any character."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller is controlling %s."), *ControlledCharacter->GetName());
	}

	ABaseCharacter* PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller can't find any player character."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller has found player character %s."), *PlayerCharacter->GetName());
	}
}

ABaseCharacter* ACharacter1AIController::GetControlledCharacter() const
{
	return Cast<ABaseCharacter>(GetPawn());
}

ABaseCharacter* ACharacter1AIController::GetPlayerCharacter() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerController) { return nullptr; }
	return Cast<ABaseCharacter>(PlayerController);
}

void ACharacter1AIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto ControlledCharacter = Cast<ABaseCharacter>(InPawn);
		if (!ensure(ControlledCharacter)) { return; }
		ControlledCharacter->OnDeath.AddUniqueDynamic(this, &ACharacter1AIController::OnCharacterDeath);
	}
}

void ACharacter1AIController::OnCharacterDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("yO"))
	UnPossess();
	Destroy(this);
}
