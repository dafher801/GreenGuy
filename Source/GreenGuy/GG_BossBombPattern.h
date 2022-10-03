
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_BossBombPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_BossBombPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom);

	virtual void Execute(class AGG_Phantom* Phantom);

	virtual void Exit(class AGG_Phantom* Phantom);

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_BossBombPattern() {}

	SGG_BossBombPattern(const SGG_BossBombPattern& BossBombPattern) {}

	SGG_BossBombPattern& operator=(const SGG_BossBombPattern& BossBombPattern) { return *this; }

};
