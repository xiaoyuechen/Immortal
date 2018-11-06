// Copyright J&J.

#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"


//////////////////////////////////////////////////////////////////////////
// AImmortalCharacter constructor

ABaseCharacter::ABaseCharacter()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(41.f, 46.0f);

	// Configure character movement
	GetCharacterMovement()->GravityScale = 8.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 2500.f;
	GetCharacterMovement()->GroundFriction = 10.0f;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->MaxFlySpeed = 1000.0f;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create an orthographic camera (no perspective) and attach it to the boom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

//////////////////////////////////////////////////////////////////////////
// Setup Player Input


void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// follow camera control
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);

	// action control
	InputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::Fire);
	
}


////////////////////////////////////////////////////////////////////////////
// BeginPlay() and Tick()

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ResetCharacter();
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


//////////////////////////////////////////////////////////////////////////
// Player callable character actions

void ABaseCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}

}
void ABaseCharacter::Fire()
{
	if (bFireMovementFreeze)
	{
		GetWorld()->GetTimerManager().SetTimer(FireMovementFreezeTimer, FireMovementFreezeTime, false);
	}
}


bool ABaseCharacter::IsFrozen()
{
	if (!bFireMovementFreeze) 
	{
		return false;
	}
	else if (GetWorld()->GetTimerManager().GetTimerRate(FireMovementFreezeTimer) <= 0.f)
	{
		return false;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////
// Take damage and broadcast when dead
float ABaseCharacter::TakeDamage
(
	float DamageAmount,
	FDamageEvent const & DamageEvent,
	AController * EventInstigator,
	AActor * DamageCauser
)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageToApply;
}

////////////////////////////////////////////////////////////////////////////
// Reset
void ABaseCharacter::ResetCharacter()
{
	CurrentHealth = StartingHealth;
}


///////////////////////////////////////////////////////////////////////////
// Getter Functions


float ABaseCharacter::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}



