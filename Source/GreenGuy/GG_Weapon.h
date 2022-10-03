
#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/Array.h"
#include "GG_Weapon.generated.h"

UCLASS()
class GREENGUY_API UGG_Weapon : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:

	UGG_Weapon();

public:

	virtual void InitFire(class AGG_Unit* InstigatorData);

	virtual void Aim(FRotator UnitFireRotation);
	virtual void Aim(FVector UnitTargetLocation);

	virtual void ClearBullets() const;

	virtual void InitSpeedLevel() const;
	virtual void SpeedLevelUp() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere) class UPaperFlipbookComponent* Flipbook;

	UPROPERTY() TArray<class AGG_Projectile*> BulletObjectPool;

	UPROPERTY() FRotator FireRotation;
	UPROPERTY() FVector TargetLocation;

	UPROPERTY() int MaxBulletNum;
	UPROPERTY() int CurrentBulletNum;

	UPROPERTY() bool bActivated;

};
