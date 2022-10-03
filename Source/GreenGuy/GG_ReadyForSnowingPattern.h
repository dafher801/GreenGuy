
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_ReadyForSnowingPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_ReadyForSnowingPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom);

	virtual void Execute(class AGG_Phantom* Phantom);

	virtual void Exit(class AGG_Phantom* Phantom);

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_ReadyForSnowingPattern() {}

	SGG_ReadyForSnowingPattern(const SGG_ReadyForSnowingPattern& ReadyForSnowingPattern) {}

	SGG_ReadyForSnowingPattern& operator=(const SGG_ReadyForSnowingPattern& ReadyForSnowingPattern) { return *this; }

};
