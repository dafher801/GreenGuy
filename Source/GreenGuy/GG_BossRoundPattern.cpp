
#include "GG_BossRoundPattern.h"

SGG_BossRoundPattern* SGG_BossRoundPattern::GetInstance()
{
	static SGG_BossRoundPattern BossRoundPattern;
	return &BossRoundPattern;
}

void SGG_BossRoundPattern::Enter(AGG_Phantom* Phantom)
{
	UE_LOG(LogTemp, Log, TEXT("Round Enter"));
}

void SGG_BossRoundPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->RoundPattern(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_BossRoundPattern::Exit(AGG_Phantom* Phantom)
{
	UE_LOG(LogTemp, Log, TEXT("Round Exit"));
}

bool SGG_BossRoundPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return true;
}
