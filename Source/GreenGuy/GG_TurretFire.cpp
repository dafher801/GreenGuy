
#include "GG_TurretFire.h"
#include "GG_Turret.h"
#include "GG_TurretWeapon.h"

SGG_TurretFire* SGG_TurretFire::GetInstance()
{
	static SGG_TurretFire TurretFire;
	return &TurretFire;
}

void SGG_TurretFire::Enter(AGG_Turret* Turret)
{

}

void SGG_TurretFire::Execute(AGG_Turret* Turret)
{
	if (Turret->Weapon && 1.0f / Turret->CurrentStatus.AttackSpeed - 
		(Turret->TimeElapsedSinceAttack += Turret->GetWorld()->DeltaTimeSeconds) <= 0)
	{
		Turret->Weapon->InitFire(Turret);
		Turret->TimeElapsedSinceAttack = 0.0f;
	}
}

void SGG_TurretFire::Exit(AGG_Turret* Turret)
{

}

bool SGG_TurretFire::OnMessage(AGG_Turret* Turret, const FString& Telegram)
{
	return true;
}