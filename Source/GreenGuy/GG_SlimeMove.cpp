
#include "GG_SlimeMove.h"
#include "GG_Slime.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GG_SlimeReadyForDash.h"
#include "GG_Player.h"

SGG_SlimeMove* SGG_SlimeMove::GetInstance()
{
	static SGG_SlimeMove SlimeMove;
	return &SlimeMove;
}

void SGG_SlimeMove::Enter(AGG_Slime* Slime)
{
	Slime->CurrentDashCoolTime = Slime->MaxDashCoolTime;
	Slime->Movement->MaxSpeed = Slime->CurrentStatus.MoveSpeed;
}

void SGG_SlimeMove::Execute(AGG_Slime* Slime)
{
	float Distance = FVector::Dist(Slime->GetActorLocation(), Slime->Player->GetActorLocation());

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Slime->GetWorld());
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Slime->Controller, Slime->Player->GetActorLocation());

	Slime->Look();

	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	if ((Slime->CurrentDashCoolTime -= Slime->GetWorld()->DeltaTimeSeconds) <= 0.0f &&
		Distance < Slime->MaxDashRange && Distance > Slime->MinDashRange)
	{
		Slime->PlayerLocation = Slime->Player->GetActorLocation();
		Slime->GetStateMachine()->ChangeState(SGG_SlimeReadyForDash::GetInstance());
	}
}

void SGG_SlimeMove::Exit(AGG_Slime* Slime)
{
	Slime->Movement->Velocity = FVector::ZeroVector;
}

bool SGG_SlimeMove::OnMessage(AGG_Slime* Slime, const FString& Telegram)
{
	return true;
}
