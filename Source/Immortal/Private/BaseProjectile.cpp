// CopyRight J&J

#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	DestroyDelay = 10.f;
	ProjectileDamage = 5.f;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovement->ProjectileGravityScale = 0.2f;
	CollisionMesh->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);

}

void ABaseProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}


void ABaseProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyDamage
	(
		OtherActor,
		ProjectileDamage,
		GetWorld()->GetFirstPlayerController(),
		this,
		UDamageType::StaticClass()
	);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseProjectile::OnTimerExpire, DestroyDelay, false);
}

void ABaseProjectile::OnTimerExpire()
{
	Destroy();
}
