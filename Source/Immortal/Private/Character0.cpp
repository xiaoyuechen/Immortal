// Copyright J&J

#include "Character0.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Public/DrawDebugHelpers.h"

void ACharacter0::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
	DrawFiringSphere();
}

void ACharacter0::Fire()
{
	if (GetWorld()->GetTimerManager().GetTimerRate(CooldownTimer) <= 0)
	{
		bIsFiring = true;
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

		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, WeaponCooldownTime, false);
	}
}

void ACharacter0::DrawFiringSphere()
{
	if (bIsFiring)
	{
		DrawDebugSphere
		(
			GetWorld(),
			GetActorLocation(),
			DamageRadius,
			8,
			FColor(0, 0, 255),
			false
		);
	}
}


