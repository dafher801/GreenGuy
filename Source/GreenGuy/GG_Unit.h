
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GG_ObjectDataTable.h"
#include "GG_Unit.generated.h"

UCLASS()
class GREENGUY_API AGG_Unit : public APawn
{
	GENERATED_BODY()
	
public:

	AGG_Unit();

public:

	virtual void Init();

	virtual void Tick(float DeltaTime);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	bool GetActivated() const;
	virtual void SetActivated(bool Activated);

	UFUNCTION(BlueprintCallable)
		FGG_Status GetCurrentStatus() const;

	class FGG_SteeringBehavior* GetSteeringBehavior() const;

	class UGG_Weapon* GetWeapon() const;

	class UFloatingPawnMovement* GetMovement() const;

	bool GetWhenHitDestroyBullet() const;

protected:

	virtual void BeginPlay() override;

	virtual void Move();
	virtual void Aim();
	virtual void Fire(float DeltaTime);

protected:

	UPROPERTY(EditAnywhere) class UShapeComponent* ShapeCollision;

	UPROPERTY(EditAnywhere) class UPaperFlipbookComponent* Flipbook;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* FrontFlipbook;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* BackFlipbook;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* LeftFlipbook;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* RightFlipbook;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) class UGG_Weapon* Weapon;

	UPROPERTY(EditAnywhere) class UFloatingPawnMovement* Movement;

	class FGG_SteeringBehavior* SteeringBehavior;

	UPROPERTY(EditAnywhere) FGG_Status BaseStatus;
	UPROPERTY() FGG_Status CurrentStatus;

	UPROPERTY() FVector MoveVector;

	UPROPERTY() float TimeElapsedSinceAttack;

	UPROPERTY() bool bActivated;

	UPROPERTY() bool bWhenHitDestroyBullet;
};
