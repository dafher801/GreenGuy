
#pragma once

#include "CoreMinimal.h"
#include "GG_State.h"

template <typename GG_ObjectType>
class TGG_StateMachine
{
public:

	TGG_StateMachine(GG_ObjectType* Owner);

public:

	void ChangeState(TGG_State<GG_ObjectType>* NewState);

	void Enter();

	void Execute();

	void Exit();

	TGG_State<GG_ObjectType>* GetPreviousState() const;

	TGG_State<GG_ObjectType>* GetCurrentState() const;

	TGG_State<GG_ObjectType>* GetGlobalState() const;

	void SetGlobalState(TGG_State<GG_ObjectType>* NewState);

	void RevertToPreviousState();

	bool HandleMessage(GG_ObjectType* Object, const FString& Telegram) const;

private:

	GG_ObjectType* Owner;

	TGG_State<GG_ObjectType>* PreviousState;

	TGG_State<GG_ObjectType>* CurrentState;

	TGG_State<GG_ObjectType>* GlobalState;
};

template<typename GG_ObjectType>
inline TGG_StateMachine<GG_ObjectType>::TGG_StateMachine(GG_ObjectType* Owner)
	: Owner(Owner)
	, PreviousState(nullptr)
	, CurrentState(nullptr)
	, GlobalState(nullptr) {}

template<typename GG_ObjectType>
inline void TGG_StateMachine<GG_ObjectType>::ChangeState(TGG_State<GG_ObjectType>* NewState)
{
	if (CurrentState)
		CurrentState->Exit(Owner);

	PreviousState = CurrentState;
	CurrentState = NewState;

	if (CurrentState)
		CurrentState->Enter(Owner);
}

template<typename GG_ObjectType>
inline void TGG_StateMachine<GG_ObjectType>::Enter()
{
	if (GlobalState)
		GlobalState->Enter(Owner);

	if (CurrentState)
		CurrentState->Enter(Owner);
}

template<typename GG_ObjectType>
inline void TGG_StateMachine<GG_ObjectType>::Execute()
{
	if (GlobalState)
		GlobalState->Execute(Owner);

	if (CurrentState)
		CurrentState->Execute(Owner);
}

template<typename GG_ObjectType>
inline void TGG_StateMachine<GG_ObjectType>::Exit()
{
	if (GlobalState)
		GlobalState->Exit(Owner);

	if (CurrentState)
		CurrentState->Exit(Owner);
}

template<typename GG_ObjectType>
inline TGG_State<GG_ObjectType>* TGG_StateMachine<GG_ObjectType>::GetPreviousState() const
{
	return PreviousState;
}

template<typename GG_ObjectType>
inline TGG_State<GG_ObjectType>* TGG_StateMachine<GG_ObjectType>::GetCurrentState() const
{
	return CurrentState;
}

template<typename GG_ObjectType>
inline TGG_State<GG_ObjectType>* TGG_StateMachine<GG_ObjectType>::GetGlobalState() const
{
	return GlobalState;
}

template<typename GG_ObjectType>
inline void TGG_StateMachine<GG_ObjectType>::SetGlobalState(TGG_State<GG_ObjectType>* NewState)
{
	GlobalState = NewState;
}

template<typename GG_ObjectType>
inline void TGG_StateMachine<GG_ObjectType>::RevertToPreviousState()
{
	ChangeState(PreviousState);
}

template<typename GG_ObjectType>
inline bool TGG_StateMachine<GG_ObjectType>::HandleMessage(GG_ObjectType* Object, const FString& Telegram) const
{
	if (CurrentState && CurrentState->OnMessage(Object, Telegram))
		return true;

	if (GlobalState && GlobalState->OnMessage(Object, Telegram))
		return true;

	return false;
}
