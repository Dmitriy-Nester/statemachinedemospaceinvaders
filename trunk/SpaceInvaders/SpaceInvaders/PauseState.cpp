#include "STDAFX.H"
#include <irrlicht.h>
#include "PauseState.hpp"

PauseState::PauseState(irr::IrrlichtDevice* d):device(d[0])
{
	this->driver = device.getVideoDriver();
	this->manager = device.getSceneManager();
	this->guienv = this->manager->getGUIEnvironment();
}

void PauseState::Update()
{
	driver->beginScene();
	manager->drawAll();
	guienv->drawAll();
	driver->endScene();
}

void PauseState::PrepareToStop()
{
	this->PauseMessage->remove();
	this->device.setEventReceiver(NULL);
}

bool PauseState::MayUpdate()
{
	return device.run();
}

void PauseState::Start()
{
	this->PauseMessage = guienv->addStaticText(L"PAUSE",irr::core::recti(20,20,160,60),1);
	this->PauseMessage->setOverrideColor(irr::video::SColor(255,255,0,0));
	this->device.setEventReceiver(&Receiver);
	Receiver.keyUP = false;
	Receiver.machine = this->_Machine;
}

bool PauseState::PauseReceiver::OnEvent(const irr::SEvent& _event)
{
	if(_event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if(_event.KeyInput.Key == irr::KEY_PAUSE&&keyUP)
											machine->PopState();
		else 
			keyUP = true;
	}
	return false;
}