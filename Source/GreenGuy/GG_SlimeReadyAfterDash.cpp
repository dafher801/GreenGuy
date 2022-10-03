
#include "GG_SlimeReadyAfterDash.h"
#include "GG_Slime.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GG_SlimeReadyForDash.h"
#include "GG_SlimeMove.h"

SGG_SlimeReadyAfterDash* SGG_SlimeReadyAfterDash::GetInstance()
{
	static SGG_SlimeReadyAfterDash SlimeReadyAfterDash;
	return &SlimeReadyAfterDash;
}

void SGG_SlimeReadyAfterDash::Enter(AGG_Slime* Slime)
{
	Slime->TimeUntilMove = Slime->ReadyAfterDashTime;
	Slime->Movement->MaxSpeed = 0.0f;
}

void SGG_SlimeReadyAfterDash::Execute(AGG_Slime* Slime)
{
	if ((Slime->TimeUntilMove -= Slime->GetWorld()->DeltaTimeSeconds) <= 0.0f)
	{
		Slime->GetStateMachine()->ChangeState(SGG_SlimeMove::GetInstance());
	}
}

void SGG_SlimeReadyAfterDash::Exit(AGG_Slime* Slime)
{
}

bool SGG_SlimeReadyAfterDash::OnMessage(AGG_Slime* Slime, const FString& Telegram)
{
	return true;
}
