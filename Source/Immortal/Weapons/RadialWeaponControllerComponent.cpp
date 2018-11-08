// Copyright J&J

#include "RadialWeaponControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Public/DrawDebugHelpers.h"

// Sets default values for this component's properties
URadialWeaponControllerComponent::URadialWeaponControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URadialWeaponControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void URadialWeaponControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShouldDrawSphere && bActuallyFired == true)
	{
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), DamageRadius, 8, FColor(0, 0, 255), false, -1.0f, (uint8)'\000', 3.0f);

	}

}

void URadialWeaponControllerComponent::Fire()
{
	if (GetWorld()->GetTimerManager().GetTimerRate(CooldownTimer) <= 0)
	{
		UGameplayStatics::ApplyRadialDamage(this, Damage, GetOwner()->GetActorLocation(), DamageRadius, UDamageType::StaticClass(), { GetOwner() }, GetOwner());
		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, WeaponCooldownTime, false);
		bActuallyFired = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Yamm"));
		bActuallyFired = false;
	}
}

