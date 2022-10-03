
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class SGG_BossShotPattern : public TGG_State<AGG_Phantom>
{
public:

	static SGG_BossShotPattern* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom) override;

	virtual void Execute(class AGG_Phantom* Phantom) override;

	virtual void Exit(class AGG_Phantom* Phantom) override;

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_BossShotPattern() {}

	SGG_BossShotPattern(const SGG_BossShotPattern& BossShotPattern) {}

	SGG_BossShotPattern& operator=(const SGG_BossShotPattern& BossShotPattern) { return *this; }

};
