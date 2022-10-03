
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Player.h"

class SGG_PlayerMove : public TGG_State<AGG_Player>
{
public:

	static SGG_PlayerMove* GetInstance();

	virtual void Enter(class AGG_Player* Player);

	virtual void Execute(class AGG_Player* Player);

	virtual void Exit(class AGG_Player* Player);

	virtual bool OnMessage(class AGG_Player* Player, const FString& Telegram) override;

private:

	SGG_PlayerMove() {}

	SGG_PlayerMove(const SGG_PlayerMove& PlayerMove) {}

	SGG_PlayerMove& operator=(const SGG_PlayerMove& PlayerMove) { return *this; }

};
