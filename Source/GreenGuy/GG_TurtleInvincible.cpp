
#include "GG_TurtleInvincible.h"
#include "GG_TurtleComeOut.h"
#include "GG_Turtle.h"
#include "GG_BasicBullet.h"
#include "Components/ShapeComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"

SGG_TurtleInvincible* SGG_TurtleInvincible::GetInstance()
{
	static SGG_TurtleInvincible TurtleInvincible;
	return &TurtleInvincible;
}

void SGG_TurtleInvincible::Enter(AGG_Turtle* Turtle)
{
	Turtle->Flipbook->SetFlipbook(Turtle->Direction ?
		Turtle->LeftInvincibleFlipbook : Turtle->RightInvincibleFlipbook);

	Turtle->bWhenHitDestroyBullet = false;
	Turtle->CurrentInvincibleTime = 0.0f;
}

void SGG_TurtleInvincible::Execute(AGG_Turtle* Turtle)
{
	if ((Turtle->CurrentInvincibleTime += Turtle->GetWorld()->DeltaTimeSeconds) >= Turtle->MaxInvincibleTime)
	{
		Turtle->StateMachine->ChangeState(SGG_TurtleComeOut::GetInstance());
	}
}

void SGG_TurtleInvincible::Exit(AGG_Turtle* Turtle)
{
	Turtle->bWhenHitDestroyBullet = true;
}

bool SGG_TurtleInvincible::OnMessage(AGG_Turtle* Turtle, const FString& Telegram)
{
	if (Telegram == "PlayerBulletOnHit")
	{
		Turtle->OnPlayerBulletHit->GetShapeCollision()->BodyInstance.SetCollisionProfileName("EnemyBullet");
		return true;
	}
	
	return false;
}
