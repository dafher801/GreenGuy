
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Turret;

class SGG_TurretLoad : public TGG_State<AGG_Turret>
{
public:

	static SGG_TurretLoad* GetInstance();

	virtual void Enter(class AGG_Turret* Turret) override;

	virtual void Execute(class AGG_Turret* Turret) override;

	virtual void Exit(class AGG_Turret* Turret) override;

	virtual bool OnMessage(class AGG_Turret* Turret, const FString& Telegram) override;

private:

	SGG_TurretLoad() {}

	SGG_TurretLoad(const SGG_TurretLoad& TurretLoad) {}

	SGG_TurretLoad& operator=(const SGG_TurretLoad& TurretLoad) { return *this; }

};
