// Fill out your copyright notice in the Description page of Project Settings.

#include "Character1.h"
#include "BaseFireComponent.h"


void ACharacter1::BeginPlay()
{
	ABaseCharacter::BeginPlay();
	FireComponent = FindComponentByClass<UBaseFireComponent>();

}

void ACharacter1::Fire()
{
	if (!ensure(FireComponent)) { return; }
	FireComponent->Fire();
	if (FireComponent->GetFiringState() == EFiringState::Ready)
	{
		if (bFireMovementFreeze)
		{
			GetWorld()->GetTimerManager().SetTimer(FireMovementFreezeTimer, FireMovementFreezeTime, false);
		}
	
	}
}
