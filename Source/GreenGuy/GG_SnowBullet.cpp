
#include "GG_SnowBullet.h"
#include "GG_PhantomWeapon.h"
#include "GG_SteeringBehavior.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGG_SnowBullet::AGG_SnowBullet()
{

}

void AGG_SnowBullet::Init(FVector SpawnLocation, FRotator FireRotation, AGG_Unit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);
	
	Yaw = GetActorRotation().Yaw;
	SnowRotationPerFrame = Cast<UGG_PhantomWeapon>(InstigatorData->GetWeapon())->GetSnowRotationPerFrame();
}

void AGG_SnowBullet::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	Movement->Velocity = SteeringBehavior->Move(FRotator(0.0f, Yaw, 0.0f));
	AddActorLocalRotation(FRotator(0.0f, SnowRotationPerFrame, 0.0f));

	Yaw += SnowRotationPerFrame;

	if ((Yaw >= 270.0f && SnowRotationPerFrame >= 0.0f) || Yaw <= 90.0f && SnowRotationPerFrame <= 0.0f)
	{
		SnowRotationPerFrame *= -1;
	}
}

void AGG_SnowBullet::BeginPlay()
{
	Super::BeginPlay();
}
