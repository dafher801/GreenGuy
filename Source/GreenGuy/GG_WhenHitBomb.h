
#pragma once

#include "CoreMinimal.h"
#include "GG_Projectile.h"
#include "GG_WhenHitBomb.generated.h"

UCLASS()
class GREENGUY_API AGG_WhenHitBomb : public AGG_Projectile
{
	GENERATED_BODY()

public:

	AGG_WhenHitBomb();

public:

	virtual void Init(FVector SpawnLocation, FVector TargetLocation, class AGG_Unit* InstigatorData) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION() virtual void OnOverlapBegin(
		class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	virtual void ClearBullets() override;

protected:

	virtual void BeginPlay() override;

	void Bomb();

protected:

	UPROPERTY() TArray<class AGG_BasicBullet*> WhenHitBulletObjectPool;

	UPROPERTY() TSubclassOf<class AGG_BasicBullet> WhenHitBulletClass;

	UPROPERTY() float TimeLeftUntilDestroy;
	UPROPERTY(EditAnywhere) float MaxTimeLeftUntilDestroy;

	UPROPERTY() int MaxBulletNum;

	UPROPERTY(EditAnywhere) int MaxDurability;
	UPROPERTY() int CurrentDurability;
	
};
