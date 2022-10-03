
#pragma once

#include "CoreMinimal.h"
#include "GG_Enemy.h"
#include "GG_StateMachine.h"
#include "GG_Turtle.generated.h"

UCLASS()
class GREENGUY_API AGG_Turtle : public AGG_Enemy
{
	GENERATED_BODY()

public:

	friend class SGG_TurtleWander;
	friend class SGG_TurtleInvincible;
	friend class SGG_TurtleHide;
	friend class SGG_TurtleComeOut;

public:

	AGG_Turtle();

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION() virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
		class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	TGG_StateMachine<AGG_Turtle>* GetStateMachine() const;

protected:

	virtual void BeginPlay() override;

protected:

	TGG_StateMachine<AGG_Turtle>* StateMachine;

	class AGG_BasicBullet* OnPlayerBulletHit;

	UPROPERTY(EditAnywhere) class UPaperFlipbook* LeftWanderFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* RightWanderFlipbook;

	UPROPERTY(EditAnywhere) class UPaperFlipbook* LeftInvincibleFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* RightInvincibleFlipbook;

	UPROPERTY(EditAnywhere) class UPaperFlipbook* LeftHideFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* RightHideFlipbook;

	UPROPERTY(EditAnywhere) class UPaperFlipbook* LeftComeOutFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* RightComeOutFlipbook;

	UPROPERTY(EditAnywhere) float MaxWanderTime;
	UPROPERTY() float CurrentWanderTime;

	UPROPERTY(EditAnywhere) float MaxInvincibleTime;
	UPROPERTY() float CurrentInvincibleTime;

	UPROPERTY(EditAnywhere) float MaxHideTime;
	UPROPERTY() float CurrentHideTime;

	UPROPERTY(EditAnywhere) float MaxComeOutTime;
	UPROPERTY() float CurrentComeOutTime;

	UPROPERTY() float RandYaw;

	// Left->true, Right->false
	UPROPERTY() bool Direction;
	
};
