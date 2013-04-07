// SpaceInvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StateMachine.hxx"
#include "Menuirrstate.h"

int main()
{
	MenuIRRState startmenu;
	StateMachine StateManipulator = StateMachine(&startmenu);
	StateManipulator.Update();
	return 0;
}