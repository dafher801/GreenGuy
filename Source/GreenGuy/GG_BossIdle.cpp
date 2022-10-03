
#include "GG_BossIdle.h"

SGG_BossIdle* SGG_BossIdle::GetInstance()
{
	static SGG_BossIdle BossIdle;
	return &BossIdle;
}

void SGG_BossIdle::Enter(AGG_Phantom* Phantom)
{

}

void SGG_BossIdle::Execute(AGG_Phantom* Phantom)
{

}

void SGG_BossIdle::Exit(AGG_Phantom* Phantom)
{

}

bool SGG_BossIdle::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return true;
}
