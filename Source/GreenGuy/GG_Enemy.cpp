
#include "GG_Enemy.h"
#include "GG_Player.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

AGG_Enemy::AGG_Enemy()
{
	Tags.Add("Enemy");
}

void AGG_Enemy::Init()
{
	Super::Init();

	SpawnDefaultController();
}

void AGG_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGG_Enemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AGG_Player>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void AGG_Enemy::Move()
{
	Super::Move();
}

void AGG_Enemy::Aim()
{
	Super::Aim();

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

void AGG_Enemy::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}

AGG_Player* AGG_Enemy::GetPlayer() const
{
	return Player;
}
