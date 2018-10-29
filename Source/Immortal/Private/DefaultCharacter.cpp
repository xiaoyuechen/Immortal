// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DefaultCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AImmortalCharacter
ADefaultCharacter::ADefaultCharacter()
{
	// Ignore PlayerController rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Configure character movement
	GetCharacterMovement()->GravityScale = 8.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 2500.f;
	GetCharacterMovement()->GroundFriction = 10.0f;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->MaxFlySpeed = 1000.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	// Setup Character
	StartingHealth = 10;
	CurrentHealth = StartingHealth;
	Damage = 1;
	DamageRadius = 200;
}

//////////////////////////////////////////////////////////////////////////
// Setup Player Input

void ADefaultCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::MoveRight);
	InputComponent->BindAction("Fire", IE_Repeat, this, &ADefaultCharacter::Fire);
}


////////////////////////////////////////////////////////////////////////////
// BeginPlay() and Tick()

void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	ResetCharacter();
}

void ADefaultCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}


//////////////////////////////////////////////////////////////////////////
// Player callable character actions

void ADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ADefaultCharacter::Fire()
{
	UGameplayStatics::ApplyRadialDamage
	(
		this,
		Damage,
		GetActorLocation(),
		DamageRadius,
		UDamageType::StaticClass(),
		{ this },
		this
	);
}

//////////////////////////////////////////////////////////////////////////
// Take damage and broadcast when dead
float ADefaultCharacter::TakeDamage
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
void ADefaultCharacter::ResetCharacter()
{
	CurrentHealth = StartingHealth;
}


///////////////////////////////////////////////////////////////////////////
// Getter Functions

float ADefaultCharacter::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}


//////////////////////////////////////////////////////////////////////////
// Graphical update

void ADefaultCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (TravelDirection < 0.0f)
	{
		SetActorRotation(FRotator(0.0, 180.0f, 0.0f));
	}
	else if (TravelDirection > 0.0f)
	{
		SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

//////////////////////////////////////////////////////////////////////////
// Animation

void ADefaultCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();

	// Are we moving or standing still?

	UPaperFlipbook* DesiredAnimation = (abs(PlayerVelocity.X) > 0.0f) ? RunningAnimation : IdleAnimation;
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}
