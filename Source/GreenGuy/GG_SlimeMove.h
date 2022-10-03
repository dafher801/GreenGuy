
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Slime;

class SGG_SlimeMove : public TGG_State<AGG_Slime>
{
public:

	static SGG_SlimeMove* GetInstance();

	virtual void Enter(class AGG_Slime* Slime) override;

	virtual void Execute(class AGG_Slime* Slime) override;

	virtual void Exit(class AGG_Slime* Slime) override;

	virtual bool OnMessage(class AGG_Slime* Slime, const FString& Telegram) override;

private:

	SGG_SlimeMove() {}

	SGG_SlimeMove(const SGG_SlimeMove& SlimeMove) {}

	SGG_SlimeMove& operator=(const SGG_SlimeMove& SlimeMove) { return *this; }

};
