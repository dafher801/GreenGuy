
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Slime;

class SGG_SlimeDivision : public TGG_State<AGG_Slime>
{
public:

	static SGG_SlimeDivision* GetInstance();

	virtual void Enter(class AGG_Slime* Slime) override;

	virtual void Execute(class AGG_Slime* Slime) override;

	virtual void Exit(class AGG_Slime* Slime) override;

	virtual bool OnMessage(class AGG_Slime* Slime, const FString& Telegram) override;

private:

	SGG_SlimeDivision() {}

	SGG_SlimeDivision(const SGG_SlimeDivision& SlimeDivision) {}

	SGG_SlimeDivision& operator=(const SGG_SlimeDivision& SlimeDivision) { return *this; }

};
