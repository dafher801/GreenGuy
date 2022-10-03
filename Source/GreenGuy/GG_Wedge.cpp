
#include "GG_Wedge.h"
#include "GG_Enemy.h"
#include "GG_Player.h"
#include "GG_SteeringBehavior.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

AGG_Wedge::AGG_Wedge()
{

}

void AGG_Wedge::Init(FVector SpawnLocation, FRotator FireRotation, class AGG_Unit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);
}

void AGG_Wedge::Tick(float DeltaTime)
{
	if (bActivated)
		Super::Tick(DeltaTime);
}

void AGG_Wedge::BeginPlay()
{
	Super::BeginPlay();
}
