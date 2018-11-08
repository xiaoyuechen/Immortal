// Fill out your copyright notice in the Description page of Project Settings.

#include "ImmortalAIController.h"
#include "Components/CapsuleComponent.h"
#include "../Characters/ImmortalCharacter.h"
#include "../Player/ImmortalPlayerController.h"


AImmortalAIController::AImmortalAIController()
{
}

void AImmortalAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		PossessedCharacter = Cast<AImmortalCharacter>(InPawn);
		if (!ensure(PossessedCharacter)) { return; }
		PossessedCharacter->OnDeath.AddUniqueDynamic(this, &AImmortalAIController::OnCharacterDeath);
	}
}

void AImmortalAIController::BeginPlay()
{
	Super::BeginPlay();
	//if (!PossessedCharacter)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Character1AI controller is not controlling any character."));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Character1AI controller is controlling %s."), *PossessedCharacter->GetName());
	//	PossessedCharacter->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AImmortalAIController::OnHit);
	//}

	PlayerCharacter = GetPlayerCharacter();
	//if (!PlayerCharacter)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Character1AI controller can't find any player character."));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Character1AI controller has found player character %s."), *PlayerCharacter->GetName());
	//}
}

void AImmortalAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (!(PossessedCharacter&&PlayerCharacter)) { return; }
	//FVector VectorToPlayerCharacter = PlayerCharacter->GetActorLocation()- PossessedCharacter->GetActorLocation();
	//float Distance = (VectorToPlayerCharacter).Size();
	//if (Distance > DetectRadius)
	//{
	//	PossessedCharacter->MoveRight(MovementDirectionMod);
	//}
	//else
	//{
	//	// TODO Acceptance radius
	//	MovementDirectionMod = NormalizeDirection(VectorToPlayerCharacter.X);
	//	PossessedCharacter->MoveRight(MovementDirectionMod);
	//	if (VectorToPlayerCharacter.X > 0.f)
	//	{
	//		PossessedCharacter->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	//	}
	//	else
	//	{
	//		PossessedCharacter->SetActorRotation(FRotator(0.f, 180.f, 0.f));
	//	}
	//	if (!PossessedCharacter->IsFrozen() && Distance < AttackRadius)
	//	{
	//		PossessedCharacter->Fire();

	//	}
	//}
}


AImmortalCharacter* AImmortalAIController::GetPlayerCharacter() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return nullptr; }
	
	if (!Cast<AImmortalPlayerController>(PlayerController)) { return nullptr; }
	Cast<AImmortalPlayerController>(PlayerController)->OnSwap.AddUniqueDynamic(this, &AImmortalAIController::OnPlayerSwap);
	return Cast<AImmortalCharacter>(PlayerController->GetPawn());
}


void AImmortalAIController::OnCharacterDeath()
{
	UnPossess();
	Destroy(this);
}

void AImmortalAIController::OnPlayerSwap()
{
	//auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	//if (!PlayerController) { return; }
	//PlayerController->OnSwap.RemoveDynamic(this, &ACharacter1AIController::OnPlayerSwap);
	PlayerCharacter = GetPlayerCharacter();
}

void AImmortalAIController::OnHit(
	UPrimitiveComponent * HitComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComponent,
	FVector NormalImpulse,
	const FHitResult & Hit
)
{
}

float AImmortalAIController::NormalizeDirection(float DirX)
{
	if (DirX > 0.f)
	{
		return 1.f;
	}
	return -1.f;
}
