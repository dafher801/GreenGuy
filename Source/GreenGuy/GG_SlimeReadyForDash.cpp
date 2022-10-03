
#include "GG_SlimeReadyForDash.h"
#include "GG_Slime.h"
#include "GG_SteeringBehavior.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GG_SlimeDash.h"

SGG_SlimeReadyForDash* SGG_SlimeReadyForDash::GetInstance()
{
	static SGG_SlimeReadyForDash SlimeReadyForDash;
	return &SlimeReadyForDash;
}

void SGG_SlimeReadyForDash::Enter(AGG_Slime* Slime)
{
	Slime->TimeUntilDash = Slime->ReadyForDashTime;
	Slime->PlayerLocation = Slime->Player->GetActorLocation();
	Slime->Movement->Velocity = FVector::ZeroVector;
	Slime->Movement->MaxSpeed = 0.0f;
}

void SGG_SlimeReadyForDash::Execute(AGG_Slime* Slime)
{
	if ((Slime->TimeUntilDash -= Slime->GetWorld()->GetDeltaSeconds()) <= 0.0f)
	{
		Slime->GetStateMachine()->ChangeState(SGG_SlimeDash::GetInstance());
	}
}

void SGG_SlimeReadyForDash::Exit(AGG_Slime* Slime)
{

}

bool SGG_SlimeReadyForDash::OnMessage(AGG_Slime* Slime, const FString& Telegram)
{
	return true;
}