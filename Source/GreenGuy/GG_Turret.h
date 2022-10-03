
#pragma once

#include "CoreMinimal.h"
#include "GG_Enemy.h"
#include "GG_StateMachine.h"
#include "GG_Turret.generated.h"

UCLASS()
class GREENGUY_API AGG_Turret : public AGG_Enemy
{
	GENERATED_BODY()

public:

	friend class SGG_TurretFire;
	friend class SGG_TurretLoad;

public:

	AGG_Turret();

public:

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	TGG_StateMachine<AGG_Turret>* GetStateMachine() const;

protected:

	virtual void BeginPlay() override;

protected:

	TGG_StateMachine<AGG_Turret>* StateMachine;

	UPROPERTY(EditAnywhere) float MaxLoadTime;
	UPROPERTY() float CurrentLoadTime;
	
};
