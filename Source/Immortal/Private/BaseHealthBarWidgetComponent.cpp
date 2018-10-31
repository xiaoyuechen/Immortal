// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHealthBarWidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseHealthBarWidget.h"


UBaseHealthBarWidgetComponent::UBaseHealthBarWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetObj(TEXT("/Game/UI/BP_BaseHealthBarWidget"));
	if (HealthBarWidgetObj.Succeeded())
	{
		SetWidgetClass(HealthBarWidgetObj.Class);
		UE_LOG(LogTemp, Warning, TEXT("Called"));	
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
		UE_LOG(LogTemp, Warning, TEXT("Found"));
		auto ParentCharacter = Cast<ABaseCharacter>(GetOwner());
		if (ParentCharacter)
		{
			Cast<UBaseHealthBarWidget>(GetUserWidgetObject())->SetParentCharacter(ParentCharacter);
		}
	}

}
