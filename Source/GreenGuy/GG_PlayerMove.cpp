
#include "GG_PlayerMove.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_PlayerMove* SGG_PlayerMove::GetInstance()
{
	static SGG_PlayerMove PlayerMove;
	return &PlayerMove;
}

void SGG_PlayerMove::Enter(AGG_Player* Player)
{
	Player->SetPlayerMoveFlipbook();
	Player->GetMovement()->MaxSpeed = Player->GetCurrentStatus().MoveSpeed;
}

void SGG_PlayerMove::Execute(AGG_Player* Player)
{
	Player->Move(Player->GetWorld()->DeltaTimeSeconds);
}

void SGG_PlayerMove::Exit(AGG_Player* Player)
{
}

bool SGG_PlayerMove::OnMessage(AGG_Player* Player, const FString& Telegram)
{
	return false;
}
