#include "STDAFX.H"
#include "StateMachine.hxx"

StateMachine::StateMachine(StateMachine::_state *StartState)
{
	StartState->SetMachine(this);
	CurrentState = StartState;
}

void StateMachine::Update()
{
	while(CurrentState->MayUpdate())
					CurrentState->Update();
}

void StateMachine::PushState(StateMachine::_state *_newstate)
{
	CurrentState->PrepareToStop();
	StatesStack.push_back(CurrentState);
	_newstate->SetMachine(this);
	_newstate->Start();
	CurrentState = _newstate;
}

StateMachine::_state* StateMachine::PopState()
{
	_state* prevstate = CurrentState;
	prevstate->PrepareToStop();
	CurrentState = StatesStack.back();
	StatesStack.pop_back();
	CurrentState->Start();
	return prevstate;
}