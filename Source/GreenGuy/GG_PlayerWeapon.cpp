
#include "GG_PlayerWeapon.h"
#include "GG_BasicBullet.h"
#include "GG_ObjectDataTable.h"
#include "GG_Unit.h"
#include "Components/ShapeComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

UGG_PlayerWeapon::UGG_PlayerWeapon()
{
	CLASS_FINDER(AGG_BasicBullet) BP_PlayerBullet = TEXT("/Game/Blueprints/GGBP_PlayerBullet");
	PlayerBulletClass = BP_PlayerBullet.Class;

	MaxBulletNum = 20;
}

void UGG_PlayerWeapon::InitFire(AGG_Unit* InstigatorData)
{
	Super::InitFire(InstigatorData);

	for (int i = CurrentBulletNum++; i < MaxBulletNum; i++)
	{
		BulletObjectPool[i]->Init(GetComponentLocation(), FireRotation, InstigatorData);
		BulletObjectPool[i]->GetShapeCollision()->BodyInstance.SetCollisionProfileName("PlayerBullet");
		return;
	}
}

void UGG_PlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<AGG_BasicBullet>(PlayerBulletClass));
}
