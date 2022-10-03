
#include "GG_TurretLoad.h"
#include "GG_TurretFire.h"
#include "GG_Turret.h"

SGG_TurretLoad* SGG_TurretLoad::GetInstance()
{
	static SGG_TurretLoad TurretLoad;
	return &TurretLoad;
}

void SGG_TurretLoad::Enter(AGG_Turret* Turret)
{

}

void SGG_TurretLoad::Execute(AGG_Turret* Turret)
{
	if ((Turret->CurrentLoadTime += Turret->GetWorld()->DeltaTimeSeconds) >= Turret->MaxLoadTime)
	{
		Turret->StateMachine->ChangeState(SGG_TurretFire::GetInstance());
		Turret->CurrentLoadTime = 0.0f;
	}
}

void SGG_TurretLoad::Exit(AGG_Turret* Turret)
{

}

bool SGG_TurretLoad::OnMessage(AGG_Turret* Turret, const FString& Telegram)
{
	return true;
}
