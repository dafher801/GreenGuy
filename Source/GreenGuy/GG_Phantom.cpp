
#include "GG_Phantom.h"
#include "GG_PhantomWeapon.h"
#include "GG_ReadyForRoundPattern.h"
#include "GG_BossBombPattern.h"
#include "GG_BossShotPattern.h"
#include "GG_BossSeekPattern.h"
#include "GG_Player.h"
#include "GG_SteeringBehavior.h"
#include "GG_GameModeBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AGG_Phantom::AGG_Phantom()
{
	Weapon = CreateDefaultSubobject<UGG_PhantomWeapon>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	MagicCircleFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MagicCircleFlipbook"));
	MagicCircleFlipbook->SetupAttachment(RootComponent);

	StateMachine = new TGG_StateMachine<AGG_Phantom>(this);

	BaseStatus = FGG_Status(100.0f, 10.0f, 2.0f, 0.0f, 500.0f, 1000.0f);
	CurrentStatus = BaseStatus;

	SetActivated(true);
}

void AGG_Phantom::Init()
{
	Super::Init();

	StateMachine->ChangeState(SGG_BossShotPattern::GetInstance());

	TimeElapsedSinceRound = 0.0f;
	TimeElapsedSinceBomb = 0.0f;
	TimeElapsedSinceSnowing = 0.0f;
	TimeElapsedSinceShot = 0.0f;
	CurrentSeekTime = 0.0f;
	TimeElapsedSinceSpawn = 0.0f;
}

void AGG_Phantom::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);
		StateMachine->Execute();
	}
}

float AGG_Phantom::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentStatus.HP <= 0.0f)
		Cast<AGG_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->StageClear();

	return DamageAmount;
}

TGG_StateMachine<AGG_Phantom>* AGG_Phantom::GetStateMachine() const
{
	return StateMachine;
}

void AGG_Phantom::RoundPattern(float DeltaTime)
{
	if (Weapon && RoundAttackSpeed != 0.0f && 
		!Cast<UGG_PhantomWeapon>(Weapon)->CheckRoundPatternEnd(this) && 
		1.0f / RoundAttackSpeed - (TimeElapsedSinceRound += DeltaTime) <= 0)
	{
		Cast<UGG_PhantomWeapon>(Weapon)->RoundPattern(this);
		TimeElapsedSinceRound = 0.0f;
	}
}

void AGG_Phantom::ReadyForRoundPattern(float DeltaTime)
{
	Cast<UGG_PhantomWeapon>(Weapon)->ReadyForRoundPattern(this);
	Movement->Velocity = SteeringBehavior->Seek(FVector::ZeroVector);
	CheckMagicCircle(RoundMagicCircle);
}

float AGG_Phantom::GetRoundAttackSpeed() const
{
	return RoundAttackSpeed;
}

void AGG_Phantom::BombPattern(float DeltaTime)
{
	if (Weapon && BombAttackSpeed != 0.0f &&
		!Cast<UGG_PhantomWeapon>(Weapon)->CheckBombPatternEnd(this) &&
		1.0f / BombAttackSpeed - (TimeElapsedSinceBomb += DeltaTime) <= 0)
	{
		Cast<UGG_PhantomWeapon>(Weapon)->BombPattern(this);
		TimeElapsedSinceBomb = 0.0f;
	}
}

void AGG_Phantom::ReadyForBombPattern(float DeltaTime)
{
	TimeElapsedSinceBomb = 1.0f / BombAttackSpeed;
	Cast<UGG_PhantomWeapon>(Weapon)->ReadyForBombPattern(this);
	Movement->Velocity = SteeringBehavior->Seek(FVector::ZeroVector);
	CheckMagicCircle(BombMagicCircle);
}

float AGG_Phantom::GetBombAttackSpeed() const
{
	return BombAttackSpeed;
}

void AGG_Phantom::ShotPattern(float DeltaTime)
{
	if ((CurrentShotTime += DeltaTime) < MaxShotTime ||
		FVector::Dist(Player->GetActorLocation(), GetActorLocation()) <= MinDistanceWithPlayer)
	{
		if (Weapon && ShotAttackSpeed != 0.0f &&
			1.0f / ShotAttackSpeed - (TimeElapsedSinceShot += DeltaTime) <= 0.0f)
		{
			Cast<UGG_PhantomWeapon>(Weapon)->ShotPattern(this);
			TimeElapsedSinceShot = 0.0f;
		}
	}
	else
	{
		CurrentShotTime = 0.0f;
		StateMachine->ChangeState(SGG_BossSeekPattern::GetInstance());
	}
}

float AGG_Phantom::GetShotAttackSpeed() const
{
	return ShotAttackSpeed;
}

void AGG_Phantom::SeekPattern(float DeltaTime)
{
	if ((CurrentSeekTime += DeltaTime) >= MaxSeekTime || 
		FVector::Dist(Player->GetActorLocation(), GetActorLocation()) <= MinDistanceWithPlayer)
	{
		CurrentSeekTime = 0.0f;
		StateMachine->ChangeState(SGG_BossShotPattern::GetInstance());
	}
	else
	{
		Movement->Velocity = SteeringBehavior->Seek(Player->GetActorLocation());
	}	
}

float AGG_Phantom::GetSeekMovementSpeed() const
{
	return SeekMovementSpeed;
}

void AGG_Phantom::SnowingPattern(float DeltaTime)
{
	if (Weapon && SnowingAttackSpeed != 0.0f &&
		!Cast<UGG_PhantomWeapon>(Weapon)->CheckSnowingPatternEnd(this) &&
		1.0f / SnowingAttackSpeed - (TimeElapsedSinceSnowing += DeltaTime) <= 0)
	{
		Cast<UGG_PhantomWeapon>(Weapon)->SnowingPattern(this);
		TimeElapsedSinceSnowing = 0.0f;
	}
}

void AGG_Phantom::ReadyForSnowingPattern(float DeltaTime)
{
	Cast<UGG_PhantomWeapon>(Weapon)->ReadyForSnowingPattern(this);
	Movement->Velocity = SteeringBehavior->Seek(FVector::ZeroVector);
	CheckMagicCircle(SnowingMagicCircle);
}

float AGG_Phantom::GetSnowingAttackSpeed() const
{
	return SnowingAttackSpeed;
}

void AGG_Phantom::SpawnEnemy(float DeltaTime)
{
	if ((TimeElapsedSinceSpawn += DeltaTime) >= SpawnTime)
	{
		TimeElapsedSinceSpawn = 0.0f;
		Cast<AGG_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SpawnEnemy();
	}
}

float AGG_Phantom::GetSpawnTime() const
{
	return SpawnTime;
}

void AGG_Phantom::CheckMagicCircle(UPaperFlipbook* MagicCircle)
{
	if (FVector::Dist2D(GetActorLocation(), FVector::ZeroVector) <= (Movement->GetMaxSpeed() / 10.0f))
	{
		MagicCircleSetFlipbook(MagicCircle);
	}
}

void AGG_Phantom::MagicCircleSetFlipbook(UPaperFlipbook* MagicCircle)
{
	bool FlipbookVisible = MagicCircleFlipbook->SetFlipbook(MagicCircle);

	MagicCircleFlipbook->SetHiddenInGame(FlipbookVisible);
	MagicCircleFlipbook->SetComponentTickEnabled(!FlipbookVisible);
}

void AGG_Phantom::BeginPlay()
{
	Super::BeginPlay();

	StateMachine->ChangeState(SGG_BossSeekPattern::GetInstance());
}

void AGG_Phantom::Move()
{
	Super::Move();
}

void AGG_Phantom::Aim()
{
	Super::Aim();

	if (Weapon && Player)
		Weapon->Aim(Player->GetActorLocation());
}

void AGG_Phantom::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}
