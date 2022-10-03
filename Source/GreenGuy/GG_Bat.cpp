
#include "GG_Bat.h"
#include "GG_BatWeapon.h"
#include "GG_BatSeek.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NavigationSystem.h"
#include "GG_Player.h"

AGG_Bat::AGG_Bat()
{
	Tags.Add("Enemy");

	Weapon = CreateDefaultSubobject<UGG_BatWeapon>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	StateMachine = new TGG_StateMachine<AGG_Bat>(this);
	StateMachine->ChangeState(SGG_BatSeek::GetInstance());

	BaseStatus = FGG_Status(500.0f, 100.0f, 2.0f, 0.0f, 200.0f, 1000.0f);
	CurrentStatus = BaseStatus;
}

void AGG_Bat::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);
		StateMachine->Execute();
	}
}

void AGG_Bat::Seek()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	UNavigationSystemV1::SimpleMoveToLocation(Controller, Player->GetActorLocation());

	Aim();
	Fire(GetWorld()->DeltaTimeSeconds);
}

TGG_StateMachine<AGG_Bat>* AGG_Bat::GetStateMachine() const
{
	return StateMachine;
}

void AGG_Bat::Aim()
{
	Super::Aim();

	FVector FireVector = Player->GetActorLocation() - GetActorLocation();
	FireVector.Z = 0.0f;

	if (Weapon && Player)
		Weapon->Aim(FireVector.Rotation());
}

void AGG_Bat::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}

void AGG_Bat::BeginPlay()
{
	Super::BeginPlay();
}
