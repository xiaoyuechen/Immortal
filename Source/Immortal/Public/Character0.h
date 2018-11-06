// Copyright J&J

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Character0.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_API ACharacter0 : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void Fire() override;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float Damage = 3.f;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float DamageRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float WeaponCooldownTime = 1.f;

	void DrawFiringSphere();

	FTimerHandle CooldownTimer;
};
