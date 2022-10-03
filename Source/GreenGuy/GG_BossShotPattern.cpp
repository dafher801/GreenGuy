
#include "GG_BossShotPattern.h"

SGG_BossShotPattern* SGG_BossShotPattern::GetInstance()
{
	static SGG_BossShotPattern BossShotPatter;
	return &BossShotPatter;
}

void SGG_BossShotPattern::Enter(AGG_Phantom* Phantom)
{

}

void SGG_BossShotPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->SnowingPattern(Phantom->GetWorld()->DeltaTimeSeconds);

	if (GetInstance() == Phantom->GetStateMachine()->GetCurrentState())
		Phantom->ShotPattern(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_BossShotPattern::Exit(AGG_Phantom* Phantom)
{

}

bool SGG_BossShotPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
