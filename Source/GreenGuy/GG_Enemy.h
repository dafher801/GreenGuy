
#pragma once

#include "CoreMinimal.h"
#include "GG_Unit.h"
#include "GG_Enemy.generated.h"

UCLASS()
class GREENGUY_API AGG_Enemy : public AGG_Unit
{
	GENERATED_BODY()

public:

	AGG_Enemy();

public:

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	class AGG_Player* GetPlayer() const;

protected:

	virtual void BeginPlay() override;

	virtual void Move() override;
	virtual void Aim() override;
	virtual void Fire(float DeltaTime) override;

protected:

	class AGG_Player* Player;
	FVector PlayerLocation;
	
};
