
#include "GG_SlimeDie.h"

SGG_SlimeDie* SGG_SlimeDie::GetInstance()
{
	static SGG_SlimeDie SlimeDie;
	return &SlimeDie;
}

void SGG_SlimeDie::Enter(AGG_Slime* Slime)
{

}

void SGG_SlimeDie::Execute(AGG_Slime* Slime)
{

}

void SGG_SlimeDie::Exit(AGG_Slime* Slime)
{

}

bool SGG_SlimeDie::OnMessage(AGG_Slime* Slime, const FString& Telegram)
{
	return true;
}