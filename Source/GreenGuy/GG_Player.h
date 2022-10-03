
#pragma once

#include "CoreMinimal.h"
#include "GG_Unit.h"
#include "GG_StateMachine.h"
#include "Components/Image.h"
#include "Containers/Array.h"
#include "GG_Player.generated.h"

UCLASS(Blueprintable)
class GREENGUY_API AGG_Player : public AGG_Unit
{
	GENERATED_BODY()

public:

	friend class SGG_PlayerKnockBack;

	AGG_Player();

public:

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	void Idle(float DeltaTime);

	void Move(float DeltaTime);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetPlayerIdleFlipbook();

	void SetPlayerMoveFlipbook();

	TGG_StateMachine<AGG_Player>* GetStateMachine() const;

protected:

	virtual void BeginPlay() override;

	virtual void Aim() override;
	virtual void Fire(float DeltaTime) override;

	virtual void InputMoveUpDownValue(float InputValue);
	virtual void InputMoveLeftRightValue(float InputValue);
	virtual void InputAttackUpDownValue(float InputValue);
	virtual void InputAttackLeftRightValue(float InputValue);

protected:

	TGG_StateMachine<AGG_Player>* StateMachine;

	UPROPERTY(EditAnywhere) class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere) class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere) class UPaperFlipbook* LeftIdleFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* RightIdleFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* LeftMoveFlipbook;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* RightMoveFlipbook;

	UPROPERTY() float CurrentMoveUpDownValue;
	UPROPERTY() float CurrentMoveLeftRightValue;
	UPROPERTY() float CurrentAttackUpDownValue;
	UPROPERTY() float CurrentAttackLeftRightValue;

	UImage* Image;
	
};
