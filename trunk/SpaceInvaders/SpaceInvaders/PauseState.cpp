#include "STDAFX.H"
#include <irrlicht.h>
#include "PauseState.hpp"

PauseState::PauseState(irr::IrrlichtDevice* d):device(d[0])
{
	;
}

void PauseState::Update()
{
	;
}

void PauseState::PrepareToStop()
{
}

bool PauseState::MayUpdate()
{
	return device.run();
}

void PauseState::Start()
{
	;
}