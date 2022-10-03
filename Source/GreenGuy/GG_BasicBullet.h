
#pragma once

#include "CoreMinimal.h"
#include "GG_Projectile.h"
#include "GG_BasicBullet.generated.h"

UCLASS()
class GREENGUY_API AGG_BasicBullet : public AGG_Projectile
{
	GENERATED_BODY()

public:

	AGG_BasicBullet();

public:

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AGG_Unit* InstigatorData) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION() virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
		class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	UFUNCTION() virtual void OnOverlapBegin(
		class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

protected:

	float Damage;
	
};
