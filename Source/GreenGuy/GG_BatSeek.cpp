
#include "GG_BatSeek.h"
#include "GG_Bat.h"

SGG_BatSeek* SGG_BatSeek::GetInstance()
{
	static SGG_BatSeek BatSeek;
	return &BatSeek;
}

void SGG_BatSeek::Enter(AGG_Bat* Bat)
{
}

void SGG_BatSeek::Execute(AGG_Bat* Bat)
{
	Bat->Seek();
}

void SGG_BatSeek::Exit(AGG_Bat* Bat)
{
}

bool SGG_BatSeek::OnMessage(AGG_Bat* Bat, const FString& Telegram)
{
	return true;
}
