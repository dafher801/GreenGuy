
#pragma once

#include "CoreMinimal.h"
#include "GG_Enemy.h"
#include "GG_StateMachine.h"
#include "GG_Bat.generated.h"

UCLASS()
class GREENGUY_API AGG_Bat : public AGG_Enemy
{
	GENERATED_BODY()

public:

	AGG_Bat();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Seek();

	TGG_StateMachine<AGG_Bat>* GetStateMachine() const;

protected:

	virtual void BeginPlay();

	virtual void Aim() override;
	virtual void Fire(float DeltaTime) override;

protected:

	TGG_StateMachine<AGG_Bat>* StateMachine;
	
};
