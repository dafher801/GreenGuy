
#include "GG_BossSeekPattern.h"
#include "GG_ObjectDataTable.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_BossSeekPattern* SGG_BossSeekPattern::GetInstance()
{
	static SGG_BossSeekPattern BossSeekPattern;
	return &BossSeekPattern;
}

void SGG_BossSeekPattern::Enter(AGG_Phantom* Phantom)
{
	Phantom->GetMovement()->MaxSpeed = Phantom->GetSeekMovementSpeed();
}

void SGG_BossSeekPattern::Execute(AGG_Phantom* Phantom)
{
	Phantom->SnowingPattern(Phantom->GetWorld()->DeltaTimeSeconds);

	if (GetInstance() == Phantom->GetStateMachine()->GetCurrentState())
		Phantom->SeekPattern(Phantom->GetWorld()->DeltaTimeSeconds);
}

void SGG_BossSeekPattern::Exit(AGG_Phantom* Phantom)
{
	Phantom->GetMovement()->MaxSpeed = Phantom->GetCurrentStatus().MoveSpeed;
}

bool SGG_BossSeekPattern::OnMessage(AGG_Phantom* Phantom, const FString& Telegram)
{
	return false;
}
