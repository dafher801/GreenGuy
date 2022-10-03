
#pragma once

#include "CoreMinimal.h"
#include "GG_Slime.h"
#include "Containers/Array.h"
#include "GG_BigSlime.generated.h"

UCLASS()
class GREENGUY_API AGG_BigSlime : public AGG_Slime
{
	GENERATED_BODY()

public:

	AGG_BigSlime();

public:

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void ClearSlime();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY() TArray<class AGG_MiddleSlime*> MiddleSlimeArray;

	UPROPERTY() TSubclassOf<class AGG_MiddleSlime> MiddleSlimeClass;
	
};
