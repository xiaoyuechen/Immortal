// Copyright J&J.

#include "ImmortalCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"


//////////////////////////////////////////////////////////////////////////
// AImmortalCharacter constructor

AImmortalCharacter::AImmortalCharacter()
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
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,50.f);
	CameraBoom->bUsePawnControlRotation = true;

	// Create an orthographic camera (no perspective) and attach it to the boom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

//////////////////////////////////////////////////////////////////////////
// Setup Player Input


void AImmortalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// follow camera control
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AImmortalCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AImmortalCharacter::LookUpAtRate);

	// action control
	InputComponent->BindAxis("MoveForward", this, &AImmortalCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AImmortalCharacter::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AImmortalCharacter::Fire);
	InputComponent->BindAction("Fire", IE_Released, this, &AImmortalCharacter::StopFiring);

	
}


////////////////////////////////////////////////////////////////////////////
// BeginPlay() and Tick()

void AImmortalCharacter::BeginPlay()
{
	Super::BeginPlay();
	ResetCharacter();
}

void AImmortalCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}



//////////////////////////////////////////////////////////////////////////
// Player callable character actions

void AImmortalCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AImmortalCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AImmortalCharacter::MoveForward(float Value)
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

void AImmortalCharacter::MoveRight(float Value)
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

//////////////////////////////////////////////////////////////////////////
// Take damage and broadcast when dead
float AImmortalCharacter::TakeDamage
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
void AImmortalCharacter::ResetCharacter()
{
	CurrentHealth = StartingHealth;
}


void AImmortalCharacter::RecoverHealthAtRate(float Rate)
{
	if (CurrentHealth < StartingHealth)
	{
		CurrentHealth += Rate;
	}
	else
	{
		CurrentHealth = StartingHealth;
	}

}

///////////////////////////////////////////////////////////////////////////
// Getter Functions
float AImmortalCharacter::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}