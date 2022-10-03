
#include "GG_BossBombPattern.h"

SGG_BossBombPattern* SGG_BossBombPattern::GetInstance()
{
	static SGG_BossBombPattern BossBombPattern;
	return &BossBombPattern;
}

void SGG_BossBombPattern::Enter(AGG_Phantom* Phantom)
{
}

void SGG_BossBombPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->BombPattern(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_BossBombPattern::Exit(AGG_Phantom* Phantom)
{
}

bool SGG_BossBombPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
