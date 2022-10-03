
#include "GG_Weapon.h"
#include "GG_Projectile.h"
#include "GG_Unit.h"
#include "PaperFlipbookComponent.h"

UGG_Weapon::UGG_Weapon()
	: CurrentBulletNum(0)
{
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(this);
}

void UGG_Weapon::InitFire(AGG_Unit* InstigatorData)
{
	if (CurrentBulletNum >= MaxBulletNum)
		CurrentBulletNum = 0;
}

void UGG_Weapon::Aim(FVector UnitTargetLocation)
{
	TargetLocation = UnitTargetLocation;
}

void UGG_Weapon::Aim(FRotator UnitFireRotation)
{
	FireRotation = UnitFireRotation;
	FireRotation.Pitch = 0.0f;
	FireRotation.Roll = 0.0f;
}

void UGG_Weapon::ClearBullets() const
{
	for (int i = 0; i < MaxBulletNum; i++)
		BulletObjectPool[i]->SetActivated(false);
}

void UGG_Weapon::InitSpeedLevel() const
{
}

void UGG_Weapon::SpeedLevelUp() const
{
}

bool UGG_Weapon::GetActivated() const
{
	return bActivated;
}

void UGG_Weapon::SetActivated(bool Activated)
{
	bActivated = Activated;
}

void UGG_Weapon::BeginPlay()
{
	Super::BeginPlay();
}
