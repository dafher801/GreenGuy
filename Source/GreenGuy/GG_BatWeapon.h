
#pragma once

#include "CoreMinimal.h"
#include "GG_Weapon.h"
#include "GG_BatWeapon.generated.h"

UCLASS()
class GREENGUY_API UGG_BatWeapon : public UGG_Weapon
{
	GENERATED_BODY()

public:

	UGG_BatWeapon();

public:

	virtual void InitFire(class AGG_Unit* InstigatorData) override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY() TSubclassOf<class AGG_Wedge> WedgeClass;
	
};
