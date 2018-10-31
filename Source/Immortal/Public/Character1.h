// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Character1.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_API ACharacter1 : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ACharacter1();
	//virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void Fire() override;
	
};
