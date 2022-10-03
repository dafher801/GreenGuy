
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Turtle;

class SGG_TurtleComeOut : public TGG_State<AGG_Turtle>
{
public:

	static SGG_TurtleComeOut* GetInstance();

	virtual void Enter(class AGG_Turtle* Turtle) override;

	virtual void Execute(class AGG_Turtle* Turtle) override;

	virtual void Exit(class AGG_Turtle* Turtle) override;

	virtual bool OnMessage(class AGG_Turtle* Turtle, const FString& Telegram) override;

private:

	SGG_TurtleComeOut() {}

	SGG_TurtleComeOut(const SGG_TurtleComeOut& TurtleComeOut) {}

	SGG_TurtleComeOut& operator=(const SGG_TurtleComeOut& TurtleComeOut) { return *this; }

};
