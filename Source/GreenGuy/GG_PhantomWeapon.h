
#pragma once

#include "CoreMinimal.h"
#include "GG_Weapon.h"
#include "GG_PhantomBombArea.h"
#include "GG_ObjectDataTable.h"
#include "GG_PhantomWeapon.generated.h"

UCLASS()
class GREENGUY_API UGG_PhantomWeapon : public UGG_Weapon
{
	GENERATED_BODY()

public:

	UGG_PhantomWeapon();

public:

	void RoundPattern(class AGG_Phantom* Phantom);
	void ReadyForRoundPattern(class AGG_Phantom* Phantom);
	bool CheckRoundPatternEnd(class AGG_Phantom* Phantom);

	void BombPattern(class AGG_Phantom* Phantom);
	void ReadyForBombPattern(class AGG_Phantom* Phantom);
	bool CheckBombPatternEnd(class AGG_Phantom* Phantom);

	void ShotPattern(class AGG_Phantom* Phantom);
	void SnowingPattern(class AGG_Phantom* Phantom);
	void ReadyForSnowingPattern(class AGG_Phantom* Phantom);
	bool CheckSnowingPatternEnd(class AGG_Phantom* Phantom);

	void EndPattern(class AGG_Phantom* Phantom);

	float GetSnowRotationPerFrame() const;

	virtual void ClearBullets();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY() TArray<class AGG_BasicBullet*> RoundBulletObjectPool;
	UPROPERTY() TSubclassOf<class AGG_BasicBullet> RoundBulletClass;

	UPROPERTY() TSubclassOf<class AGG_WhenNeglectBomb> WhenNeglectBombClass;
	UPROPERTY() TSubclassOf<class AGG_WhenHitBomb> WhenHitBombClass;

	UPROPERTY() TArray<class AGG_BasicBullet*> ShotBulletObjectPool;
	UPROPERTY() TSubclassOf<class AGG_BasicBullet> ShotBulletClass;

	UPROPERTY() TArray<class AGG_SnowBullet*> SnowBulletObjectPool;
	UPROPERTY() TSubclassOf<class AGG_SnowBullet> SnowBulletClass;

	UPROPERTY() int PatternNum;

	UPROPERTY(EditAnywhere, Category = "RoundPattern") float MaxRoundPatternTime;
	UPROPERTY(EditAnywhere, Category = "RoundPattern") float MaxReadyForRoundPatternTime;
	UPROPERTY() float CurrentRoundPatternTime;
	UPROPERTY() float CurrentReadyForRoundPatternTime;
	UPROPERTY() int MaxRoundBulletNum;
	UPROPERTY() int CurrentRoundBulletNum;
	UPROPERTY(EditAnywhere, Category = "RoundPattern") float RoundPatternRotation;
	UPROPERTY() float CurrentRoundPatternRotation;

	UPROPERTY(EditAnywhere, Category = "BombPattern") TArray<FGG_BombArea> BombAreaArray;
	UPROPERTY(EditAnywhere, Category = "BombPattern") float MaxBombPatternTime;
	UPROPERTY(EditAnywhere, Category = "BombPattern") float MaxReadyForBombPatternTime;
	UPROPERTY() float CurrentBombPatternTime;
	UPROPERTY() float CurrentReadyForBombPatternTime;

	UPROPERTY(EditAnywhere, Category = "SnowingPattern") float MaxSnowingPatternTime;
	UPROPERTY(EditAnywhere, Category = "SnowingPattern") float MaxReadyForSnowingPatternTime;
	UPROPERTY() float CurrentSnowingPatternTime;
	UPROPERTY() float CurrentReadyForSnowingPatternTime;
	UPROPERTY() int MaxShotBulletNum;
	UPROPERTY() int CurrentShotBulletNum;
	UPROPERTY() int MaxSnowBulletNum;
	UPROPERTY() int CurrentSnowBulletNum;
	UPROPERTY(EditAnywhere, Category = "SnowingPattern") float SnowRotationPerFrame;
	UPROPERTY(EditAnywhere, Category = "SnowingPattern") float MinSnowHorizontal;
	UPROPERTY(EditAnywhere, Category = "SnowingPattern") float MaxSnowHorizontal;
	UPROPERTY(EditAnywhere, Category = "SnowingPattern") float SnowVertical;

};
