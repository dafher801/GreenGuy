
#include "GG_Turtle.h"
#include "GG_BasicBullet.h"
#include "GG_TurtleWander.h"
#include "Components/ShapeComponent.h"

AGG_Turtle::AGG_Turtle()
{
	StateMachine = new TGG_StateMachine<AGG_Turtle>(this);
	StateMachine->ChangeState(SGG_TurtleWander::GetInstance());

	BaseStatus = FGG_Status(10000.0f, 10.0f, 2.5f, 0.0f, 200.0f, 100.0f);
	CurrentStatus = BaseStatus;
}

void AGG_Turtle::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);
		StateMachine->Execute();
	}
}

void AGG_Turtle::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	if (OtherActor->ActorHasTag("PlayerBullet"))
	{
		OnPlayerBulletHit = Cast<AGG_BasicBullet>(OtherActor);
		StateMachine->HandleMessage(this, "PlayerBulletOnHit");
	}
	else if (OtherActor->ActorHasTag("Player"))
	{
		StateMachine->HandleMessage(this, "PlayerOnHit");
	}
	else if (OtherActor->ActorHasTag("Obstacle"))
	{
		StateMachine->HandleMessage(this, "ObstacleOnHit");
	}
}

TGG_StateMachine<AGG_Turtle>* AGG_Turtle::GetStateMachine() const
{
	return StateMachine;
}

void AGG_Turtle::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentHit.AddDynamic(this, &AGG_Turtle::OnHit);
}
