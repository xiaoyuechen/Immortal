// Fill out your copyright notice in the Description page of Project Settings.

#include "ImmortalPlayerController.h"
#include "BaseCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseFireComponent.h"

AImmortalPlayerController::AImmortalPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UClass> Character0BlueprintFinder
	(
		TEXT("Class'/Game/Immortal/Characters/Character0/BP_Character0.BP_Character0_C'")
	);
	if (Character0BlueprintFinder.Succeeded())
	{
		Character0Blueprint = Character0BlueprintFinder.Object;
	}

}

void AImmortalPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		PossessedCharacter = Cast<ABaseCharacter>(InPawn);
		if (!ensure(PossessedCharacter)) { return; }
		PossessedCharacter->OnDeath.AddUniqueDynamic(this, &AImmortalPlayerController::OnCharacterDeath);
	}
}

void AImmortalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!PossessedCharacter) { return; }
	FireComponent = PossessedCharacter->FindComponentByClass<UBaseFireComponent>();
}

void AImmortalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Swap", IE_Pressed, this, &AImmortalPlayerController::SwapCharacter);
	InputComponent->BindAction("Exit", IE_Pressed, this, &AImmortalPlayerController::QuitGame);

}

void AImmortalPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrossHead();
}


void AImmortalPlayerController::SwapCharacter()
{
	ABaseCharacter* ClosestCharacter = Cast<ABaseCharacter>(GetClosestPawn());
	if (!(ClosestCharacter&&PossessedCharacter)) { return; }
	if (ClosestCharacter->GetHealthPercent() <= 0 && PossessedCharacter->GetHealthPercent() > 0)
	{
		UnPossess();
		PossessedCharacter->OnDeath.RemoveDynamic(this, &AImmortalPlayerController::OnCharacterDeath);
		Possess(ClosestCharacter);
		SetPawn(ClosestCharacter);

		FireComponent = PossessedCharacter->FindComponentByClass<UBaseFireComponent>();

		OnSwap.Broadcast();

		ClosestCharacter->ResetCharacter();
	}
}

void AImmortalPlayerController::QuitGame()
{
	ConsoleCommand("quit");
}

void AImmortalPlayerController::OnCharacterDeath()
{
	if (!Character0Blueprint) { return; }
	if (PossessedCharacter->IsA(Character0Blueprint))
	{
		OnCharacter0Death();
	}
	else
	{
		OnOtherCharacterDeadth();
	}
}

void AImmortalPlayerController::OnCharacter0Death()
{
	UE_LOG(LogTemp, Warning, TEXT("Character0 died"));
}

void AImmortalPlayerController::OnOtherCharacterDeadth()
{
	UE_LOG(LogTemp, Warning, TEXT("Other Character died"));
}

void AImmortalPlayerController::AimTowardsCrossHead()
{
	if (!FireComponent) { return; }

	
	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation))
	{
		FireComponent->RotateGunTowardsLocation(OutHitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Using Location"));

	}
	else
	{
		FVector OutLookDirection;
		GetLookDirection(OutLookDirection);
		FireComponent->RotateGunTowardsDirection(OutLookDirection);
		//UE_LOG(LogTemp, Warning, TEXT("Using Look Direction"));

	}
}

bool AImmortalPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool AImmortalPlayerController::GetLookDirection(FVector & LookDirection) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector CameraWorldLocation; // To be discarded
	// "De-project" the screen position of the crosshair to a world direction
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool AImmortalPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->
		LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("LineTraceHitLocation: %s"), *HitLocation.ToString());
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}


APawn * AImmortalPlayerController::GetClosestPawn()
{
	float ClosestDistance = SwapRadius;
	APawn* OtherPawn = nullptr;
	APawn* ClosestPawn = nullptr;
	for (FConstPawnIterator Itr(GetWorld()->GetPawnIterator()); Itr; ++Itr)
	{
		if (Itr->Get() != PossessedCharacter)
		{
			OtherPawn = Itr->Get();
			const float TempDistance = FVector::Dist(PossessedCharacter->GetActorLocation(), OtherPawn->GetActorLocation());
			if (SwapRadius > TempDistance && ClosestDistance > TempDistance)
			{
				ClosestDistance = TempDistance;
				ClosestPawn = OtherPawn;
			}
		}
	}
	return ClosestPawn;
}
