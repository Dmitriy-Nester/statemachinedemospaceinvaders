#include "STDAFX.H"
#include "StateMachine.hxx"
#include <irrlicht.h>
using namespace irr;
#include "GameState.h"
#include "AtlasCutter.hpp"
#include "Fighter.h"
#include "ResultState.h"

GameState::GameState(irr::IrrlichtDevice *d):device(d)
{
	smanager = device->getSceneManager();
	driver = smanager->getVideoDriver();
	AtlasCutter Cutter(smanager);
	Manager = new ActionManager(-247.5,340.0,0,239,-1.5,0,smanager);
	Receiver.setBackToMenuEvent(&GameState::DestroyThisAndPopPrevious,this);
	Fighter *fighter = new Fighter(smanager);	
	fighter->setJetTexture(Cutter.getTextureAtIndex(33));
	fighter->setJetRocketTexture(Cutter.getTextureAtIndex(34));
	fighter->setActionManager(Manager);
	Manager->setDestroyAnimators(Cutter.getExploseAnimator1(), Cutter.getExploseAnimator2());
	Manager->SetRocketExploseAnimator(Cutter.getRocketExploseAnimator());
	this->GamerUnit = fighter;
}

bool GameState::MayUpdate()
{
	return device->run();
}

void GameState::Start()
{
	video::ITexture* t = driver->getTexture("background.tga");
	SkyBox = smanager->addSkyBoxSceneNode(t,t,t,t,t,t);
	Camera = smanager->addCameraSceneNode(0,core::vector3df(-13.36,97,-262.62),core::vector3df(-7.5,118.8,20.8));
	then = device->getTimer()->getTime();
	scene::ILightSceneNode* Light = smanager->addLightSceneNode(Camera,core::vector3d<f32>(0,0,0),video::SColorf(1.0,1.0,1.0),400);
	device->setEventReceiver(&Receiver);
}

void GameState::Update()
{
	driver->beginScene(1, 1, video::SColor(255,199,10,15));
	smanager->drawAll();
	driver->endScene();
	now = device->getTimer()->getTime();
	GamerUnit->setFrameDelta((now-then)/1000.0);
	Manager->Update((now-then)/1000.0);
	then = now;	
	if(Manager->HaveResult())
		this->SwitchToRezultScreen(*Manager->HaveResult());
}

void GameState::SwitchToRezultScreen(bool result)
{
	//printf("You %s\n", result?"WIN":"lose");
	ResultState* newSt = new ResultState(this->device,result);
	_Machine->PushState(newSt);
}

void GameState::PrepareToStop()
{
	Camera->remove();
	SkyBox->remove();
	device->setEventReceiver(NULL);
}

void GameState::GameEventReceiver::setBackToMenuEvent(void (*funk)(GameState*), GameState* argu)
{
	this->BackToMenu = funk;
	BTM = argu;
}

bool GameState::GameEventReceiver::OnEvent(const SEvent& _event)
{
	if(_event.EventType == EET_KEY_INPUT_EVENT)
	{
		switch(_event.KeyInput.Key)
		{
			case 27:
				this->BackToMenu(BTM);
			break;
			case KEY_SPACE:
				BTM->GamerUnit->Fire();
				break;
			case KEY_RIGHT:
			case KEY_KEY_D:
				BTM->GamerUnit->MoveRight();
				break;
			case KEY_LEFT:
			case KEY_KEY_A:
				BTM->GamerUnit->MoveLeft();
				break;
		}
	}
	return 0;
}

void GameState::DestroyThisAndPopPrevious(GameState *self)
{
	self->_Machine->PopState();
	delete self;
}

GameState::~GameState()
{
	delete GamerUnit;
	delete Manager;
	device->setEventReceiver(NULL);
	smanager->clear();	
}