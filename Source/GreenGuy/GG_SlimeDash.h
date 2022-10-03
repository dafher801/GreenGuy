
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Slime;

class SGG_SlimeDash : public TGG_State<AGG_Slime>
{
public:

	static SGG_SlimeDash* GetInstance();

	virtual void Enter(class AGG_Slime* Slime) override;

	virtual void Execute(class AGG_Slime* Slime) override;

	virtual void Exit(class AGG_Slime* Slime) override;

	virtual bool OnMessage(class AGG_Slime* Slime, const FString& Telegram) override;

private:

	SGG_SlimeDash() {}

	SGG_SlimeDash(const SGG_SlimeDash& SlimeDash) {}

	SGG_SlimeDash& operator=(const SGG_SlimeDash& SlimeDash) { return *this; }

};
