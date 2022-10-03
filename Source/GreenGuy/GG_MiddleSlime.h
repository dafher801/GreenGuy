
#pragma once

#include "CoreMinimal.h"
#include "GG_Slime.h"
#include "GG_MiddleSlime.generated.h"

UCLASS()
class GREENGUY_API AGG_MiddleSlime : public AGG_Slime
{
	GENERATED_BODY()

public:

	AGG_MiddleSlime();

public:

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void ClearSlime();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY() TArray<class AGG_SmallSlime*> SmallSlimeArray;

	UPROPERTY() TSubclassOf<class AGG_SmallSlime> SmallSlimeClass;
	
};
