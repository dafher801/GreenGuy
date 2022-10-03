
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

class AGG_Bat;

class SGG_BatSeek : public TGG_State<AGG_Bat>
{
public:

	static SGG_BatSeek* GetInstance();

	virtual void Enter(AGG_Bat* Bat) override;

	virtual void Execute(AGG_Bat* Bat) override;

	virtual void Exit(AGG_Bat* Bat) override;

	virtual bool OnMessage(class AGG_Bat* Bat, const FString& Telegram) override;

private:

	SGG_BatSeek() {}

	SGG_BatSeek(const SGG_BatSeek& BatSeek) {}

	SGG_BatSeek& operator=(const SGG_BatSeek& BatSeek) { return *this; }

};
