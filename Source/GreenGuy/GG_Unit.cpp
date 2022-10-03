
#include "GG_Unit.h"
#include "GG_Weapon.h"
#include "GG_PlayerWeapon.h"
#include "GG_SteeringBehavior.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"

AGG_Unit::AGG_Unit()
{
	PrimaryActorTick.bCanEverTick = true;

	ShapeCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = ShapeCollision;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SteeringBehavior = new FGG_SteeringBehavior(this, Movement);

	bWhenHitDestroyBullet = true;

	SetActivated(false);

	
}

void AGG_Unit::Init()
{
	SetActivated(true);

	CurrentStatus = BaseStatus;

	TimeElapsedSinceAttack = 0.0f;
}

void AGG_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location.Z = 0.0f;
	SetActorLocation(Location);
}

float AGG_Unit::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount -= CurrentStatus.DEF;

	if (DamageAmount > 0.0f)
		CurrentStatus.HP -= DamageAmount;
	else
		DamageAmount = 0.0f;

	if (CurrentStatus.HP <= 0.0f)
	{
		SetActivated(false);
		DetachFromControllerPendingDestroy();
	}

	return DamageAmount;
}

bool AGG_Unit::GetActivated() const
{
	return bActivated;
}

void AGG_Unit::SetActivated(bool Activated)
{
	bActivated = Activated;

	Movement->SetActive(bActivated);

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

FGG_Status AGG_Unit::GetCurrentStatus() const
{
	return CurrentStatus;
}

FGG_SteeringBehavior* AGG_Unit::GetSteeringBehavior() const
{
	return SteeringBehavior;
}

UGG_Weapon* AGG_Unit::GetWeapon() const
{
	return Weapon;
}

UFloatingPawnMovement* AGG_Unit::GetMovement() const
{
	return Movement;
}

bool AGG_Unit::GetWhenHitDestroyBullet() const
{
	return bWhenHitDestroyBullet;
}

void AGG_Unit::BeginPlay()
{
	Super::BeginPlay();
}

void AGG_Unit::Move()
{

}

void AGG_Unit::Aim()
{

}

void AGG_Unit::Fire(float DeltaTime)
{
	if (Weapon && 1.0f / CurrentStatus.AttackSpeed - (TimeElapsedSinceAttack += DeltaTime) <= 0)
	{
		Weapon->InitFire(this);
		TimeElapsedSinceAttack = 0.0f;
	}
}
