
#include "GG_Turret.h"
#include "GG_TurretWeapon.h"
#include "GG_TurretFire.h"

AGG_Turret::AGG_Turret()
	: CurrentLoadTime(0.0f)
{
	Tags.Add("Enemy");

	Weapon = CreateDefaultSubobject<UGG_TurretWeapon>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	StateMachine = new TGG_StateMachine<AGG_Turret>(this);
	StateMachine->ChangeState(SGG_TurretFire::GetInstance());

	BaseStatus = FGG_Status(100.0f, 10.0f, 2.5f, 0.0f, 0.0f, 100.0f);
	CurrentStatus = BaseStatus;
}

void AGG_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StateMachine->Execute();
}

float AGG_Turret::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

TGG_StateMachine<AGG_Turret>* AGG_Turret::GetStateMachine() const
{
	return StateMachine;
}

void AGG_Turret::BeginPlay()
{
	Super::BeginPlay();
}
