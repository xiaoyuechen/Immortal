// Fill out your copyright notice in the Description page of Project Settings.

#include "ImmortalPlayerController.h"
#include "BaseCharacter.h"
#include "Engine/World.h"


void AImmortalPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ControlledCharacter = Cast<ABaseCharacter>(InPawn);
		if (!ensure(ControlledCharacter)) { return; }
		ControlledCharacter->OnDeath.AddUniqueDynamic(this, &AImmortalPlayerController::OnCharacterDeath);
	}
}

void AImmortalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Swap", IE_Pressed, this, &AImmortalPlayerController::SwapCharacter);
	InputComponent->BindAction("Exit", IE_Pressed, this, &AImmortalPlayerController::QuitGame);

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
	ABaseCharacter* ClosestCharacter = Cast<ABaseCharacter>(GetClosestPawn());
	if (!ClosestCharacter) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Closest pawn: %s"), *ClosestCharacter->GetName());
	if (ClosestCharacter->GetHealthPercent() <= 0 && ControlledCharacter->GetHealthPercent() > 0)
	{
		UnPossess();
		ControlledCharacter->OnDeath.RemoveDynamic(this, &AImmortalPlayerController::OnCharacterDeath);
		Possess(ClosestCharacter);
		SetPawn(ClosestCharacter);
		UE_LOG(LogTemp, Warning, TEXT("Player pawn now is: %s"), *ControlledCharacter->GetName());

		ClosestCharacter->ResetCharacter();
	}
}

void AImmortalPlayerController::QuitGame()
{
	ConsoleCommand("quit");
}
void AImmortalPlayerController::OnCharacterDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Character Died"));
}

APawn * AImmortalPlayerController::GetClosestPawn()
{
	float ClosestDistance = SwapRadius;
	APawn* OtherPawn = nullptr;
	APawn* ClosestPawn = nullptr;
	for (FConstPawnIterator Itr(GetWorld()->GetPawnIterator()); Itr; ++Itr)
	{
		if (Itr->Get() != ControlledCharacter)
		{
			OtherPawn = Itr->Get();
			const float TempDistance = FVector::Dist(ControlledCharacter->GetActorLocation(), OtherPawn->GetActorLocation());
			if (SwapRadius > TempDistance && ClosestDistance > TempDistance)
			{
				ClosestDistance = TempDistance;
				ClosestPawn = OtherPawn;
			}
		}
	}
	return ClosestPawn;
}
