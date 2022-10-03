
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_ReadyForRoundPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_ReadyForRoundPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom);

	virtual void Execute(class AGG_Phantom* Phantom);

	virtual void Exit(class AGG_Phantom* Phantom);

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_ReadyForRoundPattern() {}

	SGG_ReadyForRoundPattern(const SGG_ReadyForRoundPattern& ReadyForRoundPattern) {}

	SGG_ReadyForRoundPattern& operator=(const SGG_ReadyForRoundPattern& ReadyForRoundPattern) { return *this; }

};
