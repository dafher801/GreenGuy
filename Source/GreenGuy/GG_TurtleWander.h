
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Turtle;

class SGG_TurtleWander : public TGG_State<AGG_Turtle>
{
public:

	static SGG_TurtleWander* GetInstance();

	virtual void Enter(class AGG_Turtle* Turtle) override;

	virtual void Execute(class AGG_Turtle* Turtle) override;

	virtual void Exit(class AGG_Turtle* Turtle) override;

	virtual bool OnMessage(class AGG_Turtle* Turtle, const FString& Telegram) override;

private:

	SGG_TurtleWander() {}

	SGG_TurtleWander(const SGG_TurtleWander& TurtleWander) {}

	SGG_TurtleWander& operator=(const SGG_TurtleWander& TurtleWander) { return *this; }

};
