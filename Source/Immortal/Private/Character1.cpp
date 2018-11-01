// Fill out your copyright notice in the Description page of Project Settings.

#include "Character1.h"
#include "BaseFireComponent.h"

ACharacter1::ACharacter1()
{

}



void ACharacter1::BeginPlay()
{
	Super::BeginPlay();
	FireComponent = FindComponentByClass<UBaseFireComponent>();

}

void ACharacter1::Fire()
{
	if (!ensure(FireComponent)) { return; }

	FireComponent->Fire();
}
