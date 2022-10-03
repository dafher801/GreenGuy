
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Turtle;

class SGG_TurtleInvincible : public TGG_State<AGG_Turtle>
{
public:

	static SGG_TurtleInvincible* GetInstance();

	virtual void Enter(class AGG_Turtle* Turtle) override;

	virtual void Execute(class AGG_Turtle* Turtle) override;

	virtual void Exit(class AGG_Turtle* Turtle) override;

	virtual bool OnMessage(class AGG_Turtle* Turtle, const FString& Telegram) override;

private:

	SGG_TurtleInvincible() {}

	SGG_TurtleInvincible(const SGG_TurtleInvincible& TurtleInvincible) {}

	SGG_TurtleInvincible& operator=(const SGG_TurtleInvincible& TurtleInvincible) { return *this; }

};
