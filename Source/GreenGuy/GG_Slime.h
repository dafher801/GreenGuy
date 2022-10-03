
#pragma once

#include "CoreMinimal.h"
#include "GG_Enemy.h"
#include "GG_StateMachine.h"
#include "GG_Slime.generated.h"

UCLASS()
class GREENGUY_API AGG_Slime : public AGG_Enemy
{
	GENERATED_BODY()

public:

	friend class SGG_SlimeMove;
	friend class SGG_SlimeReadyForDash;
	friend class SGG_SlimeDash;
	friend class SGG_SlimeReadyAfterDash;
	friend class SGG_SlimeDivision;

public:

	AGG_Slime();

public:

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	TGG_StateMachine<AGG_Slime>* GetStateMachine() const;

protected:

	virtual void BeginPlay() override;

	virtual void Look();

	UFUNCTION() void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor, 
		class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

protected:

	TGG_StateMachine<AGG_Slime>* StateMachine;

	UPROPERTY() float TimeUntilDash;
	UPROPERTY(EditAnywhere) float ReadyForDashTime;

	UPROPERTY(EditAnywhere) float MinDashRange;
	UPROPERTY(EditAnywhere) float MaxDashRange;
	UPROPERTY(EditAnywhere) float DashSpeed;
	UPROPERTY(EditAnywhere) float MaxDashCoolTime;
	UPROPERTY() float CurrentDashCoolTime;

	UPROPERTY() float TimeUntilMove;
	UPROPERTY() float MaxDashTime;
	UPROPERTY() float CurrentDashTime;
	UPROPERTY(EditAnywhere) float ReadyAfterDashTime;

	UPROPERTY(EditAnywhere) int NumOfDivision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* ReadyForDashFlipbook;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* DashFlipbook;
	
};
