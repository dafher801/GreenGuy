
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Slime;

class SGG_SlimeReadyAfterDash : public TGG_State<AGG_Slime>
{
public:

	static SGG_SlimeReadyAfterDash* GetInstance();

	virtual void Enter(class AGG_Slime* Slime) override;

	virtual void Execute(class AGG_Slime* Slime) override;

	virtual void Exit(class AGG_Slime* Slime) override;

	virtual bool OnMessage(class AGG_Slime* Slime, const FString& Telegram) override;

private:

	SGG_SlimeReadyAfterDash() {}

	SGG_SlimeReadyAfterDash(const SGG_SlimeReadyAfterDash& SlimeReadyAfterDash) {}

	SGG_SlimeReadyAfterDash& operator=(const SGG_SlimeReadyAfterDash& SlimeReadyAfterDash) { return *this; }
};
