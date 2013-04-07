#include "STDAFX.h"
#include <irrlicht.h>
using namespace irr;
#include "ResultState.h"

ResultState::ResultState(irr::IrrlichtDevice *d, bool rez)
{
	this->device = d;
	this->GameResult = rez;
	this->Envir = device->getGUIEnvironment();
	this->Smanager = device->getSceneManager();
	this->message = Envir->addStaticText(GameResult?L"You Win":L"You Lose", core::rect<int>(60,70, 400, 150),1);
	this->driver = Envir->getVideoDriver();
	this->BackToMenu = Envir->addButton(core::recti(10,10,150,50));
	BackToMenu->setText(L"Back to menu");
}

bool ResultState::MayUpdate()
{
	return device->run();
} 

void ResultState::PrepareToStop()
{
	message->setVisible(0);
}

void ResultState::Update()
{
	driver->beginScene(1, 1, video::SColor(255,199,10,15));
	Envir->drawAll();
	this->Smanager->drawAll();
	driver->endScene();
	if(this->BackToMenu->isPressed())
		this->BackToStart();
}

void ResultState::Start()
{
	message->setVisible(1);
}

void ResultState::BackToStart()
{
	StateMachine::_state* curstate = _Machine->PopState();//снимаем со стека состояний это состояние
	StateMachine::_state* GameState = _Machine->PopState();//снимаем игровой стейт
	delete curstate;
	delete GameState;
}  

ResultState::~ResultState()
{
	message->remove();
	BackToMenu->remove();
}