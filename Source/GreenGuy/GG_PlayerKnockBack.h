
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Player;

class SGG_PlayerKnockBack : public TGG_State<AGG_Player>
{
public:

	static SGG_PlayerKnockBack* GetInstance();

	virtual void Enter(class AGG_Player* Player) override;

	virtual void Execute(class AGG_Player* Player) override;

	virtual void Exit(class AGG_Player* Player) override;

	virtual bool OnMessage(class AGG_Player* Player, const FString& Telegram) override;

private:

	SGG_PlayerKnockBack() {}

	SGG_PlayerKnockBack(const SGG_PlayerKnockBack& PlayerKnockBack) {}

	SGG_PlayerKnockBack& operator=(const SGG_PlayerKnockBack& PlayerKnockBack) { return *this; }

};
