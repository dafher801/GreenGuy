
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Player.h"

class SGG_PlayerIdle : public TGG_State<AGG_Player>
{
public:

	static SGG_PlayerIdle* GetInstance();

	virtual void Enter(class AGG_Player* Player);

	virtual void Execute(class AGG_Player* Player);

	virtual void Exit(class AGG_Player* Player);

	virtual bool OnMessage(class AGG_Player* Player, const FString& Telegram) override;

private:

	SGG_PlayerIdle() {}

	SGG_PlayerIdle(const SGG_PlayerIdle& PlayerIdle) {}

	SGG_PlayerIdle& operator=(const SGG_PlayerIdle& PlayerIdle) { return *this; }

};
