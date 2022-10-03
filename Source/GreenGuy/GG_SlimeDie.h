
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Slime;

class SGG_SlimeDie : public TGG_State<AGG_Slime>
{
public:

	static SGG_SlimeDie* GetInstance();

	virtual void Enter(class AGG_Slime* Slime) override;

	virtual void Execute(class AGG_Slime* Slime) override;

	virtual void Exit(class AGG_Slime* Slime) override;

	virtual bool OnMessage(class AGG_Slime* Slime, const FString& Telegram) override;

private:

	SGG_SlimeDie() {}

	SGG_SlimeDie(const SGG_SlimeDie& SlimeDie) {}

	SGG_SlimeDie& operator=(const SGG_SlimeDie& SlimeDie) { return *this; }

};
