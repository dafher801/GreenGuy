
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GG_Projectile.generated.h"

UCLASS()
class GREENGUY_API AGG_Projectile : public AActor
{
	GENERATED_BODY()
	
public:

	AGG_Projectile();

public:

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AGG_Unit* InstigatorData);

	virtual void Init(FVector SpawnLocation, FVector TargetLocation, class AGG_Unit* InstigatorData);

	virtual void Tick(float DeltaTime) override;

	class FGG_SteeringBehavior* GetSteeringBehavior() const;

	class UShapeComponent* GetShapeCollision() const;

	class UProjectileMovementComponent* GetMovement() const;

	FRotator GetInitialFireRotation() const;
	FVector GetInitialTargetLocation() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

	float GetMaxSpeed() const;

	virtual void ClearBullets();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere) class UShapeComponent* ShapeCollision;

	UPROPERTY(EditAnywhere) class UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditAnywhere) class UProjectileMovementComponent* Movement;

	class FGG_SteeringBehavior* SteeringBehavior;

	UPROPERTY() FRotator InitialFireRotation;
	UPROPERTY() FVector InitialTargetLocation;

	UPROPERTY() float MaxMovementDistance;
	UPROPERTY() float CurrentMovementDistance;

	UPROPERTY() bool bActivated;

};
