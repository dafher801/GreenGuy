
#include "GG_ReadyForBombPattern.h"
#include "GG_SteeringBehavior.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_ReadyForBombPattern* SGG_ReadyForBombPattern::GetInstance()
{
	static SGG_ReadyForBombPattern ReadyForBombPattern;
	return &ReadyForBombPattern;
}

void SGG_ReadyForBombPattern::Enter(AGG_Phantom* Phantom)
{
	
}

void SGG_ReadyForBombPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->ReadyForBombPattern(Phantom->GetWorld()->DeltaTimeSeconds);
	Phantom->SpawnEnemy(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_ReadyForBombPattern::Exit(AGG_Phantom* Phantom)
{
	Phantom->MagicCircleSetFlipbook(nullptr);
}

bool SGG_ReadyForBombPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
