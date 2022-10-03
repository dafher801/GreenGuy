
#include "GG_GameModeBase.h"
#include "GG_ObjectDataTable.h"
#include "GG_Player.h"
#include "GG_Phantom.h"
#include "GG_Bat.h"
#include "GG_BigSlime.h"
#include "GG_Turtle.h"
#include "GG_Weapon.h"
#include "GG_PhantomWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AGG_GameModeBase::AGG_GameModeBase()
	: KindOfEnemyNum(1)
	, MaxEnemyNum(20)
	, CurrentEnemyNum(0)
	, bPlaying(false)
{
	for (int i = 0; i < KindOfEnemyNum; i++)
		EnemyObjectPool.Add(TArray<AGG_Enemy*>());

	CLASS_FINDER(AGG_Player) BP_PlayerClass = TEXT("/Game/Blueprints/GGBP_Player");
	PlayerClass = BP_PlayerClass.Class;

	CLASS_FINDER(AGG_Phantom) BP_PhantomClass = TEXT("/Game/Blueprints/GGBP_Phantom");
	PhantomClass = BP_PhantomClass.Class;

	CLASS_FINDER(AGG_Bat) BP_BatClass = TEXT("/Game/Blueprints/GGBP_Bat");
	BatClass = BP_BatClass.Class;

	CLASS_FINDER(AGG_BigSlime) BP_SlimeClass = TEXT("/Game/Blueprints/GGBP_BigSlime");
	SlimeClass = BP_SlimeClass.Class;

	CLASS_FINDER(AGG_Turtle) BP_TurtleClass = TEXT("/Game/Blueprints/GGBP_Turtle");
	TurtleClass = BP_TurtleClass.Class;

	this->DefaultPawnClass = PlayerClass;
}

void AGG_GameModeBase::SpawnEnemy()
{
	int Index = rand() % KindOfEnemyNum;
	FVector SpawnLocation;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn)
		return;

	do
	{
		SpawnLocation = FVector(
			FRandomStream(rand()).FRandRange(MinSpawnLocationX, MaxSpawnLocationX),
			FRandomStream(rand()).FRandRange(MinSpawnLocationY, MaxSpawnLocationY), 0.0f);

	} while (FVector::Distance(SpawnLocation, PlayerPawn->GetActorLocation()) < DistancePlayerWithEnemy);

	for (int i = CurrentEnemyNum++; i < MaxEnemyNum; i++)
	{
		if (!EnemyObjectPool[Index][i]->GetActivated())
		{
			EnemyObjectPool[Index][i]->Init();
			EnemyObjectPool[Index][i]->SetActorLocation(SpawnLocation);
			return;
		}
	}

	if (CurrentEnemyNum >= MaxEnemyNum)
		CurrentEnemyNum = 0;
}

void AGG_GameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidget)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidget)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidget);

		if (CurrentWidget)
			CurrentWidget->AddToViewport();
	}
}

void AGG_GameModeBase::StartGame()
{
	bPlaying = true;
	CurrentSpawnEnemyTime = 0.0f;

	Player->Init();
	Player->SetActorLocation(FVector::ZeroVector);

	Phantom->Init();
	Phantom->SetActorLocation(FVector(600.0f, 0.0f, 0.0f));
}

void AGG_GameModeBase::InitGame()
{
	int i, j;

	for (i = 0; i < KindOfEnemyNum; i++)
	{
		for (j = 0; j < MaxEnemyNum; j++)
		{
			EnemyObjectPool[i][j]->SetActivated(false);

			if (EnemyObjectPool[i][j]->GetWeapon())
				EnemyObjectPool[i][j]->GetWeapon()->ClearBullets();

			EnemyObjectPool[i][j]->SetActorLocation(FVector::ZeroVector);
		}
	}

	if (!bPlaying)
	{
		Player->GetWeapon()->InitSpeedLevel();
	}

	Player->SetActivated(false);
	Player->GetWeapon()->ClearBullets();
	Player->SetActorLocation(FVector::ZeroVector);

	Phantom->SetActivated(false);
	Cast<UGG_PhantomWeapon>(Phantom->GetWeapon())->ClearBullets();
	Phantom->SetActorLocation(FVector(600.0f, 0.0f, 0.0f));

	for (i = 0; i < KindOfEnemyNum; i++)
		for (j = 0; j < MaxEnemyNum; j++)
			EnemyObjectPool[i][j]->SetActivated(false);

	/*for (i = 0; i < MaxEnemyNum; i++)
		Cast<AGG_BigSlime>(EnemyObjectPool[1][i])->ClearSlime();*/
}

AGG_Player* AGG_GameModeBase::GetPlayer() const
{
	return Player;
}

AGG_Phantom* AGG_GameModeBase::GetPhantom() const
{
	return Phantom;
}

void AGG_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AGG_Player>(GetWorld()->SpawnActor<AGG_Player>(PlayerClass));
	Phantom = Cast<AGG_Phantom>(GetWorld()->SpawnActor<AGG_Phantom>(PhantomClass));

	for (int i = 0; i < MaxEnemyNum; i++)
	{
		EnemyObjectPool[0].Add(Cast<AGG_Bat>(GetWorld()->SpawnActor(BatClass)));
		/*EnemyObjectPool[1].Add(Cast<AGG_BigSlime>(GetWorld()->SpawnActor(SlimeClass)));
		EnemyObjectPool[2].Add(Cast<AGG_Turtle>(GetWorld()->SpawnActor(TurtleClass)));*/
	}

	InitGame();
}
