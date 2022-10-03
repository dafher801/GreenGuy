
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"
#include "GG_Phantom.h"

class AGG_Phantom;

class SGG_BossIdle : public TGG_State<AGG_Phantom>
{
public:

	static SGG_BossIdle* GetInstance();

	virtual void Enter(class AGG_Phantom* Phantom);

	virtual void Execute(class AGG_Phantom* Phantom);

	virtual void Exit(class AGG_Phantom* Phantom);

	virtual bool OnMessage(class AGG_Phantom* Phantom, const FString& Telegram) override;

private:

	SGG_BossIdle() {}

	SGG_BossIdle(const SGG_BossIdle& BossIdle) {}

	SGG_BossIdle& operator=(const SGG_BossIdle& BossIdle) { return *this; }

};
