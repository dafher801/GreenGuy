
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_BossSnowingPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_BossSnowingPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom) override;

	virtual void Execute(class AGG_Phantom* Phantom) override;

	virtual void Exit(class AGG_Phantom* Phantom) override;

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_BossSnowingPattern() {}

	SGG_BossSnowingPattern(const SGG_BossSnowingPattern& BossSnowingPattern) {}

	SGG_BossSnowingPattern& operator=(const SGG_BossSnowingPattern& BossSnowingPattern) { return *this; }

};
