// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHealthBarWidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseHealthBarWidget.h"


UBaseHealthBarWidgetComponent::UBaseHealthBarWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> HealthBarWidgetFinder
	(
		TEXT("Class'/Game/Immortal/UI/BP_BaseHealthBarWidget.BP_BaseHealthBarWidget_C'")
	);
	if (HealthBarWidgetFinder.Succeeded())
	{
		SetWidgetClass(HealthBarWidgetFinder.Object);
	}

	SetWidgetSpace(EWidgetSpace::Screen);
	SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	SetDrawAtDesiredSize(true);
}

void UBaseHealthBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Cast<UBaseHealthBarWidget>(Widget))
	{
		auto ParentCharacter = Cast<ABaseCharacter>(GetOwner());
		if (ParentCharacter)
		{
			Cast<UBaseHealthBarWidget>(Widget)->SetParentCharacter(ParentCharacter);
		}
	}

}
