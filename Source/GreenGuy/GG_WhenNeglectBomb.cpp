
#include "GG_WhenNeglectBomb.h"
#include "GG_BasicBullet.h"
#include "GG_SteeringBehavior.h"
#include "GG_Unit.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGG_WhenNeglectBomb::AGG_WhenNeglectBomb()
	: MaxBulletNum(6)
{
	CLASS_FINDER(AGG_BasicBullet) BP_YellowBullet = TEXT("/Game/Blueprints/GGBP_WhenNeglectBullet");
	WhenNeglectBulletClass = BP_YellowBullet.Class;
}

void AGG_WhenNeglectBomb::Init(FVector SpawnLocation, FVector TargetLocation, AGG_Unit* InstigatorData)
{
	Super::Init(SpawnLocation, TargetLocation, InstigatorData);

	CurrentDurability = MaxDurability;
	TimeLeftUntilExplosion = 0.0f;

	Movement->MaxSpeed = 300.0f;
	Movement->InitialSpeed = Movement->MaxSpeed;

	MaxMovementDistance = InstigatorData->GetCurrentStatus().Range;
	CurrentMovementDistance = 0.0f;
}

void AGG_WhenNeglectBomb::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		Movement->Velocity = SteeringBehavior->Seek(InitialTargetLocation);

		if ((TimeLeftUntilExplosion += DeltaTime) > MaxTimeLeftUntilExplosion)
		{
			Bomb();
		}
	}
}

void AGG_WhenNeglectBomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentDurability--;

	if (CurrentDurability <= 0)
		SetActivated(false);
}

void AGG_WhenNeglectBomb::ClearBullets()
{
	SetActivated(false);

	for (int i = 0; i < WhenNeglectBulletObjectPool.Num(); i++)
		WhenNeglectBulletObjectPool[i]->SetActivated(false);
}

void AGG_WhenNeglectBomb::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentBeginOverlap.AddDynamic(this, &AGG_WhenNeglectBomb::OnOverlapBegin);

	for (int i = 0; i < MaxBulletNum; i++)
		WhenNeglectBulletObjectPool.Add(GetWorld()->SpawnActor<AGG_BasicBullet>(WhenNeglectBulletClass));
}

void AGG_WhenNeglectBomb::Bomb()
{
	SetActivated(false);
	TimeLeftUntilExplosion = 0.0f;

	float yaw = 0.0f;

	for (int i = 0; i < 6; i++)
	{
		WhenNeglectBulletObjectPool[i]->Init(GetActorLocation(), 
			FRotator(0.0f, yaw, 0.0f), Cast<AGG_Unit>(GetInstigator()));

		yaw += 60.0f;
	}
}