
#pragma once

#include "CoreMinimal.h"
#include "GG_BasicBullet.h"
#include "GG_SnowBullet.generated.h"

UCLASS()
class GREENGUY_API AGG_SnowBullet : public AGG_BasicBullet
{
	GENERATED_BODY()

public:

	AGG_SnowBullet();

public:

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AGG_Unit* InstigatorData) override;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

protected:

	float Yaw;
	float SnowRotationPerFrame;
	
};
