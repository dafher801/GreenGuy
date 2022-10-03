
#include "GG_SlimeDash.h"
#include "GG_Slime.h"
#include "GG_SteeringBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GG_SlimeReadyAfterDash.h"
#include "GG_Player.h"
#include "GG_PlayerIdle.h"
#include "GG_PlayerKnockBack.h"

SGG_SlimeDash* SGG_SlimeDash::GetInstance()
{
	static SGG_SlimeDash SlimeDash;
	return &SlimeDash;
}

void SGG_SlimeDash::Enter(AGG_Slime* Slime)
{
	Slime->TimeElapsedSinceAttack = Slime->BaseStatus.ATK;

	Slime->MaxDashTime = FVector::Dist(Slime->GetActorLocation(),
		Slime->Player->GetActorLocation()) / Slime->DashSpeed;

	Slime->CurrentDashTime = Slime->MaxDashTime;
	Slime->Movement->MaxSpeed = Slime->DashSpeed;
	Slime->Movement->Velocity = Slime->SteeringBehavior->Seek(Slime->PlayerLocation);
}

void SGG_SlimeDash::Execute(AGG_Slime* Slime)
{
	Slime->Aim();

	if ((Slime->CurrentDashTime -= Slime->GetWorld()->GetDeltaSeconds()) <= 0.0f)
	{
		Slime->GetStateMachine()->ChangeState(SGG_SlimeReadyAfterDash::GetInstance());
	}
}

void SGG_SlimeDash::Exit(AGG_Slime* Slime)
{
	Slime->Player->GetStateMachine()->ChangeState(SGG_PlayerIdle::GetInstance());
}

bool SGG_SlimeDash::OnMessage(AGG_Slime* Slime, const FString& Telegram)
{
	if (Telegram == FString("PlayerOnHit"))
	{
		Slime->Player->GetMovement()->Velocity = Slime->Movement->Velocity;
		Slime->Player->GetStateMachine()->ChangeState(SGG_PlayerKnockBack::GetInstance());

		if ((Slime->TimeElapsedSinceAttack += Slime->GetWorld()->DeltaTimeSeconds) >= Slime->BaseStatus.ATK)
		{
			Slime->TimeElapsedSinceAttack = 0.0f;

			UGameplayStatics::ApplyDamage(Slime->Player, Slime->GetCurrentStatus().HP,
				UGameplayStatics::GetPlayerController(Slime->GetWorld(), 0), Slime, NULL);
		}

		return true;
	}
	else if (Telegram == FString("ObstacleOnHit") || Telegram == FString("EnemyOnHit"))
	{
		Slime->GetStateMachine()->ChangeState(SGG_SlimeReadyAfterDash::GetInstance());
		return true;
	}

	return false;
}
