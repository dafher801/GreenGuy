
#include "GG_PlayerIdle.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_PlayerIdle* SGG_PlayerIdle::GetInstance()
{
	static SGG_PlayerIdle PlayerIdle;
	return &PlayerIdle;
}

void SGG_PlayerIdle::Enter(AGG_Player* Player)
{
	Player->SetPlayerIdleFlipbook();
}

void SGG_PlayerIdle::Execute(AGG_Player* Player)
{
	Player->Idle(Player->GetWorld()->DeltaTimeSeconds);
}

void SGG_PlayerIdle::Exit(AGG_Player* Player)
{
}

bool SGG_PlayerIdle::OnMessage(AGG_Player* Player, const FString& Telegram)
{
	return true;
}