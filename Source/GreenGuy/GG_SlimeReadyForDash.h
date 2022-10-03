
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Slime;

class SGG_SlimeReadyForDash : public TGG_State<AGG_Slime>
{
public:

	static SGG_SlimeReadyForDash* GetInstance();

	virtual void Enter(class AGG_Slime* Slime) override;

	virtual void Execute(class AGG_Slime* Slime) override;

	virtual void Exit(class AGG_Slime* Slime) override;

	virtual bool OnMessage(class AGG_Slime* Slime, const FString& Telegram) override;

private:

	SGG_SlimeReadyForDash() {}

	SGG_SlimeReadyForDash(const SGG_SlimeReadyForDash& SlimeReadyForDash) {}

	SGG_SlimeReadyForDash& operator=(const SGG_SlimeReadyForDash& SlimeReadyForDash) { return *this; }

};
