
#pragma once

#include "CoreMinimal.h"
#include "GG_Weapon.h"
#include "GG_ObjectDataTable.h"
#include "Containers/Array.h"
#include "GG_TurretWeapon.generated.h"

UCLASS()
class GREENGUY_API UGG_TurretWeapon : public UGG_Weapon
{
	GENERATED_BODY()

public:

	UGG_TurretWeapon();

public:

	virtual void InitFire(class AGG_Unit* InstigatorData) override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY() TSubclassOf<class AGG_BasicBullet> TurretBulletClass;

	int MaxFireNum;
	int CurrentFireNum;
	
};
