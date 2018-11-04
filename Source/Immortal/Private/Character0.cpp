// Copyright J&J

#include "Character0.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


void ACharacter0::Fire()
{
	ABaseCharacter::Fire();
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


