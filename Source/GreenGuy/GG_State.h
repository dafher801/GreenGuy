
#pragma once

#include "CoreMinimal.h"

template <typename GG_ObjectType>
class TGG_State
{
public:

	virtual ~TGG_State() {}

public:

	virtual void Enter(GG_ObjectType* Object) = 0;

	virtual void Execute(GG_ObjectType* Object) = 0;

	virtual void Exit(GG_ObjectType* Object) = 0;

	virtual bool OnMessage(GG_ObjectType* Object, const FString& Telegram) = 0;
};
