
#include "GG_BasicBullet.h"
#include "GG_Unit.h"
#include "GG_SteeringBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGG_BasicBullet::AGG_BasicBullet()
{
	Movement->bShouldBounce = true;
}

void AGG_BasicBullet::Init(FVector SpawnLocation, FRotator FireRotation, AGG_Unit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);

	Damage = InstigatorData->GetCurrentStatus().ATK;

	MaxMovementDistance = InstigatorData->GetCurrentStatus().Range;
	CurrentMovementDistance = 0.0f;

	Movement->Velocity = SteeringBehavior->Move(InitialFireRotation);
}

void AGG_BasicBullet::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);
	}
}

void AGG_BasicBullet::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage,
		UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);

	if (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("Enemy"))
		SetActivated(!Cast<AGG_Unit>(OtherActor)->GetWhenHitDestroyBullet());
	else
		SetActivated(false);
}

void AGG_BasicBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActivated(false);
}

void AGG_BasicBullet::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentHit.AddDynamic(this, &AGG_BasicBullet::OnHit);
	ShapeCollision->OnComponentBeginOverlap.AddDynamic(this, &AGG_BasicBullet::OnOverlapBegin);
}
