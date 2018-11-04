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
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Fire")
	class UBaseFireComponent* FireComponent;
	virtual void Fire() override;
	
};
