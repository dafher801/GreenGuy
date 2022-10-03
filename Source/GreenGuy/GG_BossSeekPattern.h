
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_BossSeekPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_BossSeekPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom) override;

	virtual void Execute(class AGG_Phantom* Phantom) override;

	virtual void Exit(class AGG_Phantom* Phantom) override;

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_BossSeekPattern() {}

	SGG_BossSeekPattern(const SGG_BossSeekPattern& BossSeekPattern) {}

	SGG_BossSeekPattern& operator=(const SGG_BossSeekPattern& BossSeekPattern) { return *this; }

};
