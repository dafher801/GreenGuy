
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_ReadyForBombPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_ReadyForBombPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom) override;

	virtual void Execute(class AGG_Phantom* Phantom) override;

	virtual void Exit(class AGG_Phantom* Phantom) override;

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_ReadyForBombPattern() {}

	SGG_ReadyForBombPattern(const SGG_ReadyForBombPattern& ReadyForBombPattern) {}

	SGG_ReadyForBombPattern& operator=(const SGG_ReadyForBombPattern& ReadyForBombPattern) { return *this; }

};
