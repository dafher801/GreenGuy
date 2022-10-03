
#include "GG_ReadyForSnowingPattern.h"
#include "GG_SteeringBehavior.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_ReadyForSnowingPattern* SGG_ReadyForSnowingPattern::GetInstance()
{
	static SGG_ReadyForSnowingPattern ReadyForSnowingPattern;
	return &ReadyForSnowingPattern;
}

void SGG_ReadyForSnowingPattern::Enter(AGG_Phantom* Phantom)
{
	Phantom->GetMovement()->Velocity = Phantom->GetSteeringBehavior()->Seek(FVector::ZeroVector);
}

void SGG_ReadyForSnowingPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->ReadyForSnowingPattern(Phantom->GetWorld()->DeltaTimeSeconds);
	Phantom->SpawnEnemy(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_ReadyForSnowingPattern::Exit(AGG_Phantom* Phantom)
{
	Phantom->MagicCircleSetFlipbook(nullptr);
}

bool SGG_ReadyForSnowingPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
