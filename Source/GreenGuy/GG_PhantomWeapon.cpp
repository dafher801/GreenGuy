
#include "GG_PhantomWeapon.h"
#include "GG_BasicBullet.h"
#include "GG_WhenNeglectBomb.h"
#include "GG_WhenHitBomb.h"
#include "GG_PhantomBombArea.h"
#include "GG_SnowBullet.h"
#include "GG_Player.h"
#include "GG_Phantom.h"
#include "GG_BossRoundPattern.h"
#include "GG_ReadyForRoundPattern.h"
#include "GG_BossBombPattern.h"
#include "GG_ReadyForBombPattern.h"
#include "GG_BossShotPattern.h"
#include "GG_BossSeekPattern.h"
#include "GG_ReadyForSnowingPattern.h"
#include "GG_SteeringBehavior.h"
#include "Components/ShapeComponent.h"

UGG_PhantomWeapon::UGG_PhantomWeapon()
	: PatternNum(3)
	
	, CurrentRoundPatternTime(0.0f)
	, CurrentReadyForRoundPatternTime(0.0f)
	, MaxRoundBulletNum(480)
	, CurrentRoundBulletNum(0)
	, CurrentRoundPatternRotation(0)

	, CurrentBombPatternTime(0.0f)
	, CurrentReadyForBombPatternTime(0.0f)

	, CurrentSnowingPatternTime(0.0f)
	, CurrentReadyForSnowingPatternTime(0.0f)
	, MaxShotBulletNum(100)
	, CurrentShotBulletNum(0)
	, MaxSnowBulletNum(200)
	, CurrentSnowBulletNum(0)
{
	CLASS_FINDER(AGG_WhenNeglectBomb) BP_WhenNeglectBomb = TEXT("/Game/Blueprints/GGBP_WhenNeglectBomb");
	WhenNeglectBombClass = BP_WhenNeglectBomb.Class;

	CLASS_FINDER(AGG_WhenHitBomb) BP_WhenHitBomb = TEXT("/Game/Blueprints/GGBP_WhenHitBomb");
	WhenHitBombClass = BP_WhenHitBomb.Class;

	CLASS_FINDER(AGG_BasicBullet) BP_RoundBullet = TEXT("/Game/Blueprints/GGBP_RoundPatternBullet");
	RoundBulletClass = BP_RoundBullet.Class;

	CLASS_FINDER(AGG_BasicBullet) BP_ShotBullet = TEXT("/Game/Blueprints/GGBP_ShotPatternBullet");
	ShotBulletClass = BP_ShotBullet.Class;

	CLASS_FINDER(AGG_SnowBullet) BP_SnowBullet = TEXT("/Game/Blueprints/GGBP_SnowPatternBullet");
	SnowBulletClass = BP_SnowBullet.Class;
}

void UGG_PhantomWeapon::RoundPattern(AGG_Phantom* Phantom)
{
	float Rotation = CurrentRoundPatternRotation;

	CurrentRoundPatternRotation += RoundPatternRotation;

	if (CurrentRoundBulletNum >= MaxRoundBulletNum)
		CurrentRoundBulletNum = 0;

	for (int i = 0; i < 12; i++)
	{
		RoundBulletObjectPool[CurrentRoundBulletNum++]->Init(
			GetComponentLocation(), FRotator(0.0f, Rotation, 0.0f), Phantom);

		Rotation += 30.0f;
	}
}

void UGG_PhantomWeapon::ReadyForRoundPattern(AGG_Phantom* Phantom)
{
	if ((CurrentReadyForRoundPatternTime += Phantom->
		GetWorld()->DeltaTimeSeconds) >= MaxReadyForRoundPatternTime)
	{
		CurrentReadyForRoundPatternTime = 0.0f;
		Phantom->GetStateMachine()->ChangeState(SGG_BossRoundPattern::GetInstance());
	}
}

bool UGG_PhantomWeapon::CheckRoundPatternEnd(class AGG_Phantom* Phantom)
{
	if ((CurrentRoundPatternTime += Phantom->GetWorld()->DeltaTimeSeconds) >= MaxRoundPatternTime)
	{
		CurrentRoundPatternTime = 0.0f;
		EndPattern(Phantom);
		return true;
	}

	return false;
}

void UGG_PhantomWeapon::BombPattern(AGG_Phantom* Phantom)
{
	float RandomX;
	float RandomY;

	int i, j, k;

	for (i = 0; i < BombAreaArray.Num(); i++)
	{
		for (j = 0; j < BombAreaArray[i].Bombs.Num(); j++)
		{
			RandomX = FMath::RandRange(BombAreaArray[i].MinX, BombAreaArray[i].MaxX);
			RandomY = FMath::RandRange(BombAreaArray[i].MinY, BombAreaArray[i].MaxY);
			TargetLocation = FVector(RandomX, RandomY, 0.0f);

			if (!BombAreaArray[i].Bombs[j]->GetActivated())
			{
				for (k = 0; k < j; k++)
				{
					if (FVector::Dist(TargetLocation, BombAreaArray[i].Bombs[k]->
						GetInitialTargetLocation()) < BombAreaArray[i].MinDistanceBetweenBombs)
					{
						break;
					}
				}

				if (k >= j)
					BombAreaArray[i].Bombs[j]->Init(GetComponentLocation(), TargetLocation, Phantom);
			}
		}
	}
}

void UGG_PhantomWeapon::ReadyForBombPattern(AGG_Phantom* Phantom)
{
	if ((CurrentReadyForBombPatternTime += Phantom->
		GetWorld()->DeltaTimeSeconds) >= MaxReadyForBombPatternTime)
	{
		CurrentReadyForBombPatternTime = 0.0f;
		Phantom->GetStateMachine()->ChangeState(SGG_BossBombPattern::GetInstance());
	}
}

bool UGG_PhantomWeapon::CheckBombPatternEnd(AGG_Phantom* Phantom)
{
	if ((CurrentBombPatternTime += Phantom->GetWorld()->DeltaTimeSeconds) >= MaxBombPatternTime)
	{
		CurrentBombPatternTime = 0.0f;
		EndPattern(Phantom);
		return true;
	}

	return false;
}

void UGG_PhantomWeapon::ShotPattern(AGG_Phantom* Phantom)
{
	float ShotRotation = -60.0f;

	if (CurrentShotBulletNum >= MaxShotBulletNum)
		CurrentShotBulletNum = 0;

	AGG_Player* Player = Phantom->GetPlayer();
	FVector FireVector = Player->GetActorLocation() - Phantom->GetActorLocation();

	FireVector.Z = 0.0f;

	for (int i = 0; i < 5; i++)
	{
		Aim(FireVector.Rotation());

		ShotBulletObjectPool[CurrentShotBulletNum]->Init(GetComponentLocation(),
			FRotator(0.0f, ShotRotation, 0.0f) + FireRotation, Phantom);

		ShotBulletObjectPool[CurrentShotBulletNum++]->
			GetShapeCollision()->BodyInstance.SetCollisionProfileName("EnemyBullet");
		ShotRotation += 30.0f;
	}
}

void UGG_PhantomWeapon::SnowingPattern(AGG_Phantom* Phantom)
{
	if (CurrentSnowBulletNum >= MaxSnowBulletNum)
		CurrentSnowBulletNum = 0;

	float RandHorizontal = FMath::RandRange(MinSnowHorizontal, MaxSnowHorizontal);

	SnowBulletObjectPool[CurrentSnowBulletNum++]->Init(FVector(
		SnowVertical, RandHorizontal, 0.0f), FRotator(0.0f, 90.0f, 0.0f), Phantom);
}

void UGG_PhantomWeapon::ReadyForSnowingPattern(AGG_Phantom* Phantom)
{
	if ((CurrentReadyForSnowingPatternTime += Phantom->
		GetWorld()->DeltaTimeSeconds) >= MaxReadyForSnowingPatternTime)
	{
		CurrentReadyForSnowingPatternTime = 0.0f;
		Phantom->GetStateMachine()->ChangeState(SGG_BossSeekPattern::GetInstance());
	}
}

bool UGG_PhantomWeapon::CheckSnowingPatternEnd(AGG_Phantom* Phantom)
{
	if ((CurrentSnowingPatternTime += Phantom->GetWorld()->DeltaTimeSeconds) >= MaxSnowingPatternTime)
	{
		CurrentSnowingPatternTime = 0.0f;
		EndPattern(Phantom);
		return true;
	}

	return false;
}

void UGG_PhantomWeapon::EndPattern(AGG_Phantom* Phantom)
{
	TGG_State<AGG_Phantom>* State = Phantom->GetStateMachine()->GetCurrentState();

	while (true)
	{
		switch (FMath::Rand() % PatternNum)
		{
		case 0:
			if (SGG_BossRoundPattern::GetInstance() != State)
			{
				Phantom->GetStateMachine()->ChangeState(SGG_ReadyForRoundPattern::GetInstance());
				return;
			}

			break;

		case 1:
			if (SGG_BossBombPattern::GetInstance() != State)
			{
				Phantom->GetStateMachine()->ChangeState(SGG_ReadyForBombPattern::GetInstance());
				return;
			}

			break;

		case 2:
			if (SGG_BossShotPattern::GetInstance() != State && SGG_BossSeekPattern::GetInstance() != State)
			{
				Phantom->GetStateMachine()->ChangeState(SGG_ReadyForSnowingPattern::GetInstance());
				return;
			}

			break;

		default:
			break;
		}
	}
}

float UGG_PhantomWeapon::GetSnowRotationPerFrame() const
{
	return SnowRotationPerFrame;
}

void UGG_PhantomWeapon::ClearBullets()
{
	int i, j;

	for (i = 0; i < RoundBulletObjectPool.Num(); i++)
		RoundBulletObjectPool[i]->SetActivated(false);

	for (i = 0; i < BombAreaArray.Num(); i++)
	{
		for (j = 0; j < BombAreaArray[i].WhenNeglectBombNum + BombAreaArray[i].WhenHitBombNum; j++)
			BombAreaArray[i].Bombs[j]->ClearBullets();
	}

	for (i = 0; i < SnowBulletObjectPool.Num(); i++)
		SnowBulletObjectPool[i]->SetActivated(false);

	for (i = 0; i < ShotBulletObjectPool.Num(); i++)
		ShotBulletObjectPool[i]->SetActivated(false);

	CurrentRoundPatternTime = 0.0f;
	CurrentReadyForRoundPatternTime = 0.0f;
	CurrentRoundBulletNum = 0;
	CurrentRoundPatternRotation = 0;

	CurrentBombPatternTime = 0.0f;
	CurrentReadyForBombPatternTime = 0.0f;

	CurrentSnowingPatternTime = 0.0f;
	CurrentReadyForSnowingPatternTime = 0.0f;
	CurrentShotBulletNum = 0;
	CurrentSnowBulletNum = 0;
}

void UGG_PhantomWeapon::BeginPlay()
{
	Super::BeginPlay();

	int i, j;

	for (i = 0; i < BombAreaArray.Num(); i++)
	{
		for (j = 0; j < BombAreaArray[i].WhenNeglectBombNum; j++)
			BombAreaArray[i].Bombs.Add(GetWorld()->SpawnActor<AGG_WhenNeglectBomb>(WhenNeglectBombClass));
		
		for (j = 0; j < BombAreaArray[i].WhenHitBombNum; j++)
			BombAreaArray[i].Bombs.Add(GetWorld()->SpawnActor<AGG_WhenHitBomb>(WhenHitBombClass));
	}

	for (i = 0; i < MaxRoundBulletNum; i++)
		RoundBulletObjectPool.Add(GetWorld()->SpawnActor<AGG_BasicBullet>(RoundBulletClass));

	for (i = 0; i < MaxSnowBulletNum; i++)
		SnowBulletObjectPool.Add(GetWorld()->SpawnActor<AGG_SnowBullet>(SnowBulletClass));

	for (i = 0; i < MaxShotBulletNum; i++)
		ShotBulletObjectPool.Add(GetWorld()->SpawnActor<AGG_BasicBullet>(ShotBulletClass));
}
