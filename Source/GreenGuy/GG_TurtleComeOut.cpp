
#include "GG_TurtleComeOut.h"
#include "GG_TurtleWander.h"
#include "GG_Turtle.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

SGG_TurtleComeOut* SGG_TurtleComeOut::GetInstance()
{
	static SGG_TurtleComeOut TurtleComeOut;
	return &TurtleComeOut;
}

void SGG_TurtleComeOut::Enter(AGG_Turtle* Turtle)
{
	Turtle->Flipbook->SetFlipbook(Turtle->Direction ?
		Turtle->LeftComeOutFlipbook : Turtle->RightComeOutFlipbook);

	Turtle->CurrentComeOutTime = 0.0f;
}

void SGG_TurtleComeOut::Execute(AGG_Turtle* Turtle)
{
	if ((Turtle->CurrentComeOutTime += Turtle->GetWorld()->DeltaTimeSeconds) >= Turtle->MaxComeOutTime)
	{
		Turtle->StateMachine->ChangeState(SGG_TurtleWander::GetInstance());
	}
}

void SGG_TurtleComeOut::Exit(AGG_Turtle* Turtle)
{
}

bool SGG_TurtleComeOut::OnMessage(AGG_Turtle* Turtle, const FString& Telegram)
{
	return true;
}
