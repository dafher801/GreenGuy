
#include "GG_TurtleHide.h"
#include "GG_TurtleInvincible.h"
#include "GG_Turtle.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

SGG_TurtleHide* SGG_TurtleHide::GetInstance()
{
	static SGG_TurtleHide TurtleHide;
	return &TurtleHide;
}

void SGG_TurtleHide::Enter(AGG_Turtle* Turtle)
{
	Turtle->Flipbook->SetFlipbook(Turtle->Direction ?
		Turtle->LeftHideFlipbook : Turtle->RightHideFlipbook);

	Turtle->CurrentHideTime = 0.0f;
}

void SGG_TurtleHide::Execute(AGG_Turtle* Turtle)
{
	if ((Turtle->CurrentHideTime += Turtle->GetWorld()->DeltaTimeSeconds) >= Turtle->MaxHideTime)
	{
		Turtle->StateMachine->ChangeState(SGG_TurtleInvincible::GetInstance());
	}
}

void SGG_TurtleHide::Exit(AGG_Turtle* Turtle)
{
}

bool SGG_TurtleHide::OnMessage(AGG_Turtle* Turtle, const FString& Telegram)
{
	return true;
}

