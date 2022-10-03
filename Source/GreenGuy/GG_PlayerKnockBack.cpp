
#include "GG_PlayerKnockBack.h"
#include "GG_Player.h"

SGG_PlayerKnockBack* SGG_PlayerKnockBack::GetInstance()
{
	static SGG_PlayerKnockBack PlayerKnockBack;
	return &PlayerKnockBack;
}

void SGG_PlayerKnockBack::Enter(AGG_Player* Player)
{

}

void SGG_PlayerKnockBack::Execute(AGG_Player* Player)
{
	Player->Aim();
	Player->Fire(Player->GetWorld()->DeltaTimeSeconds);
}

void SGG_PlayerKnockBack::Exit(AGG_Player* Player)
{

}

bool SGG_PlayerKnockBack::OnMessage(AGG_Player* Player, const FString& Telegram)
{
	return true;
}