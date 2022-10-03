
#include "GG_BatWeapon.h"
#include "GG_Wedge.h"
#include "GG_Player.h"
#include "GG_Enemy.h"
#include "GG_SteeringBehavior.h"
#include "GG_ObjectDataTable.h"
#include "Components/ShapeComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"

UGG_BatWeapon::UGG_BatWeapon()
{
	CLASS_FINDER(AGG_Wedge) BP_Wedge = TEXT("/Game/Blueprints/GGBP_Wedge");
	WedgeClass = BP_Wedge.Class;

	MaxBulletNum = 20;
}

void UGG_BatWeapon::InitFire(AGG_Unit* InstigatorData)
{
	Super::InitFire(InstigatorData);

	AGG_Player* Player = Cast<AGG_Enemy>(InstigatorData)->GetPlayer();

	Aim(InstigatorData->GetSteeringBehavior()->Pursuit(Player->
		GetActorLocation(), Player->GetMovement()->Velocity).Rotation());
	BulletObjectPool[CurrentBulletNum]->Init(GetComponentLocation(), FireRotation, InstigatorData);
	BulletObjectPool[CurrentBulletNum++]->GetShapeCollision()->BodyInstance.SetCollisionProfileName("EnemyBullet");
}

void UGG_BatWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<AGG_Wedge>(WedgeClass));
}
