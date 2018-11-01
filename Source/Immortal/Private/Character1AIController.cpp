// Fill out your copyright notice in the Description page of Project Settings.

#include "Character1AIController.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "BaseCharacter.h"
#include "Character1.h"


ACharacter1AIController::ACharacter1AIController()
{
}

void ACharacter1AIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		PossessedCharacter = Cast<ABaseCharacter>(InPawn);
		if (!ensure(PossessedCharacter)) { return; }
		PossessedCharacter->OnDeath.AddUniqueDynamic(this, &ACharacter1AIController::OnCharacterDeath);
	}
}

void ACharacter1AIController::BeginPlay()
{
	Super::BeginPlay();
	if (!PossessedCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller is not controlling any character."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller is controlling %s."), *PossessedCharacter->GetName());
		PossessedCharacter->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACharacter1AIController::OnHit);
	}

	PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller can't find any player character."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character1AI controller has found player character %s."), *PlayerCharacter->GetName());
	}
}

void ACharacter1AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!(PossessedCharacter&&PlayerCharacter)) { return; }
	FVector VectorToPlayerCharacter = PlayerCharacter->GetActorLocation()- PossessedCharacter->GetActorLocation();
	float Distance = (VectorToPlayerCharacter).Size();
	if (Distance > DetectRadius)
	{
		PossessedCharacter->MoveRight(MovementDirectionMod);
	}
	else
	{
		MoveToActor(PlayerCharacter, AcceptanceRadius);
		if (VectorToPlayerCharacter.X > 0.f)
		{
			PossessedCharacter->SetActorRotation(FRotator(0.f, 0.f, 0.f));
		}
		else
		{
			PossessedCharacter->SetActorRotation(FRotator(0.f, 180.f, 0.f));
		}
		PossessedCharacter->Fire();
	}
}


ABaseCharacter* ACharacter1AIController::GetPlayerCharacter() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerController) { return nullptr; }
	return Cast<ABaseCharacter>(PlayerController);
}


void ACharacter1AIController::OnCharacterDeath()
{
	UnPossess();
	Destroy(this);
}

void ACharacter1AIController::OnHit
(
	UPrimitiveComponent * HitComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComponent,
	FVector NormalImpulse,
	const FHitResult & Hit
)
{
	MovementDirectionMod *= (-1);
}
