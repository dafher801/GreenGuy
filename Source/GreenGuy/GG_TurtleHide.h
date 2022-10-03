
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Turtle;

class SGG_TurtleHide : public TGG_State<AGG_Turtle>
{
public:

	static SGG_TurtleHide* GetInstance();

	virtual void Enter(class AGG_Turtle* Turtle) override;

	virtual void Execute(class AGG_Turtle* Turtle) override;

	virtual void Exit(class AGG_Turtle* Turtle) override;

	virtual bool OnMessage(class AGG_Turtle* Turtle, const FString& Telegram) override;

private:

	SGG_TurtleHide() {}

	SGG_TurtleHide(const SGG_TurtleHide& TurtleHide) {}

	SGG_TurtleHide& operator=(const SGG_TurtleHide& TurtleHide) { return *this; }

};
