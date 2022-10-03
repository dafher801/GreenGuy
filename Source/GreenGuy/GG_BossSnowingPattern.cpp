
#include "GG_BossSnowingPattern.h"

SGG_BossSnowingPattern* SGG_BossSnowingPattern::GetInstance()
{
	static SGG_BossSnowingPattern BossSnowingPattern;
	return &BossSnowingPattern;
}

void SGG_BossSnowingPattern::Enter(AGG_Phantom* Phantom)
{

}

void SGG_BossSnowingPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->SnowingPattern(Phantom->GetWorld()->DeltaTimeSeconds);
	Phantom->ShotPattern(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_BossSnowingPattern::Exit(AGG_Phantom* Phantom)
{

}

bool SGG_BossSnowingPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
