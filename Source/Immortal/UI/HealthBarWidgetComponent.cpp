// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "HealthBarWidget.h"


UHealthBarWidgetComponent::UHealthBarWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> HealthBarWidgetFinder
	(
		TEXT("Class'/Game/Immortal/UI/BP_HealthBarWidget.BP_HealthBarWidget_C'")
	);
	if (HealthBarWidgetFinder.Succeeded())
	{
		SetWidgetClass(HealthBarWidgetFinder.Object);
	}

	SetWidgetSpace(EWidgetSpace::Screen);
	SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	SetDrawAtDesiredSize(true);
}

void UHealthBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Cast<UHealthBarWidget>(Widget))
	{
		auto ParentCharacter = Cast<AImmortalCharacter>(GetOwner());
		if (ParentCharacter)
		{
			Cast<UHealthBarWidget>(Widget)->SetParentCharacter(ParentCharacter);
		}
	}

}
