
#include "GG_ReadyForRoundPattern.h"
#include "GG_SteeringBehavior.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_ReadyForRoundPattern* SGG_ReadyForRoundPattern::GetInstance()
{
	static SGG_ReadyForRoundPattern ReadyForRoundPattern;
	return &ReadyForRoundPattern;
}

void SGG_ReadyForRoundPattern::Enter(AGG_Phantom* Phantom)
{
	
}

void SGG_ReadyForRoundPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->ReadyForRoundPattern(Phantom->GetWorld()->DeltaTimeSeconds);
	Phantom->SpawnEnemy(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_ReadyForRoundPattern::Exit(AGG_Phantom* Phantom)
{
	Phantom->MagicCircleSetFlipbook(nullptr);
}

bool SGG_ReadyForRoundPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
