
#include "GG_TurretWeapon.h"
#include "GG_Turret.h"
#include "GG_TurretLoad.h"

UGG_TurretWeapon::UGG_TurretWeapon()
	: MaxFireNum(5)
	, CurrentFireNum(0)
{
	CLASS_FINDER(AGG_BasicBullet) BP_TurretBullet = TEXT("/Game/Blueprints/GGBP_TurretBullet");
	TurretBulletClass = BP_TurretBullet.Class;

	MaxBulletNum = 20;
}

void UGG_TurretWeapon::InitFire(AGG_Unit* InstigatorData)
{
	int i, j;

	Super::InitFire(InstigatorData);

	FireRotation = FRotator::ZeroRotator;

	for (i = 0; i < 4; i++)
	{
		for (j = CurrentBulletNum++; j < MaxBulletNum; j++)
		{
			/*if (!BulletObjectPool[j]->GetActivated())
			{
				BulletObjectPool[j]->Init(GetComponentLocation(), FireRotation, InstigatorData);
				break;
			}*/

			BulletObjectPool[j]->Init(GetComponentLocation(), FireRotation, InstigatorData);
			break;
		}

		FireRotation.Yaw += 90.0f;
	}

	if (++CurrentFireNum >= MaxFireNum)
	{
		Cast<AGG_Turret>(InstigatorData)->GetStateMachine()->ChangeState(SGG_TurretLoad::GetInstance());
		CurrentFireNum = 0;
	}
}

void UGG_TurretWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<AGG_BasicBullet>(TurretBulletClass));
}
