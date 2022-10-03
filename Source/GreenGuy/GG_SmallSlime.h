
#pragma once

#include "CoreMinimal.h"
#include "GG_Slime.h"
#include "GG_SmallSlime.generated.h"

UCLASS()
class GREENGUY_API AGG_SmallSlime : public AGG_Slime
{
	GENERATED_BODY()
	
public:

	AGG_SmallSlime();

public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

};
