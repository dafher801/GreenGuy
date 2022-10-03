
#include "GG_SlimeDivision.h"
#include "GG_Slime.h"

SGG_SlimeDivision* SGG_SlimeDivision::GetInstance()
{
	static SGG_SlimeDivision SlimeDivision;
	return &SlimeDivision;
}

void SGG_SlimeDivision::Enter(AGG_Slime* Slime)
{

}

void SGG_SlimeDivision::Execute(AGG_Slime* Slime)
{

}

void SGG_SlimeDivision::Exit(AGG_Slime* Slime)
{
}

bool SGG_SlimeDivision::OnMessage(AGG_Slime* Slime, const FString& Telegram)
{
	return true;
}