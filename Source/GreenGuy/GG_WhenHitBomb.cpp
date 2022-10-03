
#include "GG_WhenHitBomb.h"
#include "GG_BasicBullet.h"
#include "GG_SteeringBehavior.h"
#include "GG_Unit.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGG_WhenHitBomb::AGG_WhenHitBomb()
	: MaxBulletNum(6)
{
	CLASS_FINDER(AGG_BasicBullet) BP_WhenHitBullet = TEXT("/Game/Blueprints/GGBP_WhenHitBullet");
	WhenHitBulletClass = BP_WhenHitBullet.Class;
}

void AGG_WhenHitBomb::Init(FVector SpawnLocation, FVector TargetLocation, AGG_Unit* InstigatorData)
{
	Super::Init(SpawnLocation, TargetLocation, InstigatorData);

	CurrentDurability = MaxDurability;
	TimeLeftUntilDestroy = 0.0f;

	Movement->MaxSpeed = 300.0f;
	Movement->InitialSpeed = Movement->MaxSpeed;

	MaxMovementDistance = InstigatorData->GetCurrentStatus().Range;
	CurrentMovementDistance = 0.0f;
}

void AGG_WhenHitBomb::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		Movement->Velocity = SteeringBehavior->Seek(InitialTargetLocation);

		if ((TimeLeftUntilDestroy += DeltaTime) > MaxTimeLeftUntilDestroy)
		{
			SetActivated(false);
		}
	}
}

void AGG_WhenHitBomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentDurability--;

	if (CurrentDurability <= 0)
		Bomb();
}

void AGG_WhenHitBomb::ClearBullets()
{
	SetActivated(false);

	for (int i = 0; i < WhenHitBulletObjectPool.Num(); i++)
		WhenHitBulletObjectPool[i]->SetActivated(false);
}

void AGG_WhenHitBomb::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentBeginOverlap.AddDynamic(this, &AGG_WhenHitBomb::OnOverlapBegin);

	for (int i = 0; i < MaxBulletNum; i++)
		WhenHitBulletObjectPool.Add(GetWorld()->SpawnActor<AGG_BasicBullet>(WhenHitBulletClass));
}

void AGG_WhenHitBomb::Bomb()
{
	SetActivated(false);
	TimeLeftUntilDestroy = 0.0f;

	float yaw = 0.0f;

	for (int i = 0; i < MaxBulletNum; i++)
	{
		WhenHitBulletObjectPool[i]->Init(GetActorLocation(), FRotator(0.0f, yaw, 0.0f), Cast<AGG_Unit>(GetInstigator()));

		yaw += 60.0f;
	}
}