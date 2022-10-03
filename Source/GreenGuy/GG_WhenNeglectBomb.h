
#pragma once

#include "CoreMinimal.h"
#include "GG_Projectile.h"
#include "GG_ObjectDataTable.h"
#include "GG_WhenNeglectBomb.generated.h"

UCLASS()
class GREENGUY_API AGG_WhenNeglectBomb : public AGG_Projectile
{
	GENERATED_BODY()
	
public:

	AGG_WhenNeglectBomb();

public:

	virtual void Init(FVector SpawnLocation, FVector TargetLocation, class AGG_Unit* InstigatorData) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION() virtual void OnOverlapBegin(
		class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	void ClearBullets();

protected:

	virtual void BeginPlay() override;

	void Bomb();

protected:

	UPROPERTY() TArray<class AGG_BasicBullet*> WhenNeglectBulletObjectPool;

	UPROPERTY() TSubclassOf<class AGG_BasicBullet> WhenNeglectBulletClass;

	UPROPERTY() float TimeLeftUntilExplosion;
	UPROPERTY(EditAnywhere) float MaxTimeLeftUntilExplosion;

	UPROPERTY() int MaxBulletNum;

	UPROPERTY(EditAnywhere) int MaxDurability;
	UPROPERTY() int CurrentDurability;

};
