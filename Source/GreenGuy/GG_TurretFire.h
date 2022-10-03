
#pragma once

#include "GG_State.h"

class AGG_Turret;

class SGG_TurretFire : public TGG_State<AGG_Turret>
{
public:

	static SGG_TurretFire* GetInstance();

	virtual void Enter(class AGG_Turret* Turret) override;

	virtual void Execute(class AGG_Turret* Turret) override;

	virtual void Exit(class AGG_Turret* Turret) override;

	virtual bool OnMessage(class AGG_Turret* Turret, const FString& Telegram) override;

private:

	SGG_TurretFire() {}

	SGG_TurretFire(const SGG_TurretFire& TurretFire) {}

	SGG_TurretFire& operator=(const SGG_TurretFire& TurretFire) { return *this; }

};
