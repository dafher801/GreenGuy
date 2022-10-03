
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_BossRoundPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_BossRoundPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom);

	virtual void Execute(class AGG_Phantom* Phantom);

	virtual void Exit(class AGG_Phantom* Phantom);

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_BossRoundPattern() {}

	SGG_BossRoundPattern(const SGG_BossRoundPattern& BossRoundPattern) {}

	SGG_BossRoundPattern& operator=(const SGG_BossRoundPattern& BossRoundPattern) { return *this; }

};
