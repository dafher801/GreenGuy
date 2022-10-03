
#include "GG_Projectile.h"
#include "GG_Unit.h"
#include "GG_SteeringBehavior.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGG_Projectile::AGG_Projectile()
	: CurrentMovementDistance(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	ShapeCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = ShapeCollision;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0.0f;

	SteeringBehavior = new FGG_SteeringBehavior(this, Movement);

	SetActivated(false);
}

void AGG_Projectile::Init(FVector SpawnLocation, FRotator FireRotation, AGG_Unit* InstigatorData)
{
	SetActorLocation(SpawnLocation);
	SetActorRotation(FireRotation);
	SetInstigator(Cast<APawn>(InstigatorData));

	InitialFireRotation = FireRotation;

	SetActivated(true);
}

void AGG_Projectile::Init(FVector SpawnLocation, FVector TargetLocation, AGG_Unit* InstigatorData)
{
	FRotator FireRotation = (TargetLocation - GetActorLocation()).Rotation();
	FireRotation.Pitch = 0.0f;
	FireRotation.Roll = 0.0f;

	SetActorLocation(SpawnLocation);
	SetActorRotation(FireRotation);
	SetInstigator(Cast<APawn>(InstigatorData));

	InitialTargetLocation = TargetLocation;

	SetActivated(true);
}

void AGG_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FGG_SteeringBehavior* AGG_Projectile::GetSteeringBehavior() const
{
	return SteeringBehavior;
}

UShapeComponent* AGG_Projectile::GetShapeCollision() const
{
	return ShapeCollision;
}

UProjectileMovementComponent* AGG_Projectile::GetMovement() const
{
	return Movement;
}

FRotator AGG_Projectile::GetInitialFireRotation() const
{
	return InitialFireRotation;
}

FVector AGG_Projectile::GetInitialTargetLocation() const
{
	return InitialTargetLocation;
}

bool AGG_Projectile::GetActivated() const
{
	return bActivated;
}

void AGG_Projectile::SetActivated(bool Activated)
{
	bActivated = Activated;

	Movement->SetActive(bActivated);

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

float AGG_Projectile::GetMaxSpeed() const
{
	return Movement->GetMaxSpeed();
}

void AGG_Projectile::ClearBullets()
{

}

void AGG_Projectile::BeginPlay()
{
	Super::BeginPlay();
}
