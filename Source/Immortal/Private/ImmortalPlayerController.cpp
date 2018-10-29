// Fill out your copyright notice in the Description page of Project Settings.

#include "ImmortalPlayerController.h"
#include "DefaultCharacter.h"
#include "Components/SphereComponent.h"


void AImmortalPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ControlledCharacter = Cast<ADefaultCharacter>(InPawn);
		if (!ensure(ControlledCharacter)) { return; }
		ControlledCharacter->OnDeath.AddUniqueDynamic(this, &AImmortalPlayerController::OnCharacterDeath);
	}
}

void AImmortalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!ControlledCharacter) { return; }

	UE_LOG(LogTemp, Warning, TEXT("PlayerController is controlling: %s"), *ControlledCharacter->GetName());

}

void AImmortalPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void AImmortalPlayerController::SwapCharacter()
{

	if (!(ControlledCharacter)) { return; }
	TArray<AActor*> OutActorsInSwapSphere;
	ControlledCharacter->GetActorsInSwapSphere(OutActorsInSwapSphere);
	for (auto EachActor : OutActorsInSwapSphere)
	{
	UE_LOG(LogTemp, Warning, TEXT("Hello world."));
		UE_LOG(LogTemp, Warning, TEXT("%s's SwapSphere is overlapping %s"), *ControlledCharacter->GetName(), *EachActor->GetName());
		if (EachActor != ControlledCharacter)
		{
			UnPossess();
			Possess(Cast<APawn>(EachActor));
			UE_LOG(LogTemp, Warning, TEXT("Trying to possess %s."), *EachActor->GetName());
			break;
		}
	}
}
//
//void AImmortalPlayerController::Initialise(ADefaultCharacter * CharacterRef)
//{
//	ControlledCharacter = CharacterRef;
//}

void AImmortalPlayerController::OnCharacterDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Character Died"));
}



