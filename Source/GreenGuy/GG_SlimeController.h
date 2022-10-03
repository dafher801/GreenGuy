
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GG_SlimeController.generated.h"

UCLASS()
class GREENGUY_API AGG_SlimeController : public AAIController
{
	GENERATED_BODY()

public:

	AGG_SlimeController();

public:

	virtual void Tick(float DeltaTime) override;

	/*virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;*/

private:

	void OnRepeatTimer();

private:

	
	
};
