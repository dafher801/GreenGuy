
#include "GG_TurtleWander.h"
#include "GG_TurtleHide.h"
#include "GG_Turtle.h"
#include "GG_SteeringBehavior.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"

SGG_TurtleWander* SGG_TurtleWander::GetInstance()
{
	static SGG_TurtleWander TurtleWander;
	return &TurtleWander;
}

void SGG_TurtleWander::Enter(AGG_Turtle* Turtle)
{
	Turtle->RandYaw = FMath::FRandRange(0.0f, 360.0f);

	Turtle->Direction = FRotator(0.0f, Turtle->RandYaw, 0.0f).Vector().Y > 0.0f;

	Turtle->Flipbook->SetFlipbook(Turtle->Direction ? 
		Turtle->LeftWanderFlipbook : Turtle->RightWanderFlipbook);

	Turtle->CurrentWanderTime = 0.0f;
}

void SGG_TurtleWander::Execute(AGG_Turtle* Turtle)
{
	Turtle->Movement->Velocity = Turtle->SteeringBehavior->Move(FRotator(0.0f, Turtle->RandYaw, 0.0f));

	if ((Turtle->CurrentWanderTime += Turtle->GetWorld()->DeltaTimeSeconds) >= Turtle->MaxWanderTime)
	{
		Turtle->StateMachine->ChangeState(SGG_TurtleHide::GetInstance());
	}
}

void SGG_TurtleWander::Exit(AGG_Turtle* Turtle)
{
	Turtle->Movement->Velocity = FVector::ZeroVector;
}

bool SGG_TurtleWander::OnMessage(AGG_Turtle* Turtle, const FString& Telegram)
{
	if (Telegram == "ObstacleOnHit")
	{
		Turtle->RandYaw = FMath::FRandRange(0.0f, 360.0f);

		Turtle->Direction = FRotator(0.0f, Turtle->RandYaw, 0.0f).Vector().Y > 0.0f;

		Turtle->Flipbook->SetFlipbook(Turtle->Direction ?
			Turtle->LeftWanderFlipbook : Turtle->RightWanderFlipbook);

		return true;
	}
	else if (Telegram == "PlayerOnHit")
	{
		Turtle->StateMachine->ChangeState(SGG_TurtleHide::GetInstance());
		return true;
	}
	
	return false;
}
