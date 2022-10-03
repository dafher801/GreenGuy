
#include "GG_Slime.h"
#include "GG_SteeringBehavior.h"
#include "Components/ShapeComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GG_SlimeMove.h"
#include "GG_SlimeDash.h"
#include "GG_SlimeReadyAfterDash.h"
#include "GG_Player.h"
#include "GG_PlayerKnockBack.h"
#include "GG_SlimeDie.h"

AGG_Slime::AGG_Slime()
{
	BaseStatus = FGG_Status(100.0f, 10.0f, 1.0f, 0.0f, 200.0f, 100.0f);
	CurrentStatus = BaseStatus;

	StateMachine = new TGG_StateMachine<AGG_Slime>(this);
	StateMachine->ChangeState(SGG_SlimeMove::GetInstance());
}

void AGG_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StateMachine->Execute();
}

float AGG_Slime::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentStatus.HP <= 0.0f)
		StateMachine->ChangeState(SGG_SlimeDie::GetInstance());

	return Damage;
}

TGG_StateMachine<AGG_Slime>* AGG_Slime::GetStateMachine() const
{
	return StateMachine;
}

void AGG_Slime::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentHit.AddDynamic(this, &AGG_Slime::OnHit);
}

void AGG_Slime::Look()
{
	FVector LookAtVector = Player->GetActorLocation() - GetActorLocation();

	if (FMath::Abs(LookAtVector.X) > FMath::Abs(LookAtVector.Y))
	{
		if (LookAtVector.X > 0.0f)
			Flipbook->SetFlipbook(BackFlipbook);
		else
			Flipbook->SetFlipbook(FrontFlipbook);
	}
	else if (FMath::Abs(LookAtVector.X) < FMath::Abs(LookAtVector.Y))
	{
		if (LookAtVector.Y < 0.0f)
			Flipbook->SetFlipbook(RightFlipbook);
		else
			Flipbook->SetFlipbook(LeftFlipbook);
	}
}

void AGG_Slime::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	if (OtherActor->ActorHasTag("Player"))
		StateMachine->HandleMessage(this, "PlayerOnHit");

	if (OtherActor->ActorHasTag("Enemy"))
		StateMachine->HandleMessage(this, "EnemyOnHit");
}
