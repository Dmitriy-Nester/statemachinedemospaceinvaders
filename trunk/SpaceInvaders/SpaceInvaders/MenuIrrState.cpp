#include "STDAFX.H"
#include "StateMachine.hxx"
#include "MenuIrrState.h"
#include "GameState.h"

#pragma comment(lib,"irrlicht.lib")

MenuIRRState::MenuIRRState()
{
	device = createDevice(video::EDT_OPENGL, core::dimension2du(1024,768),16,0);
	driver = device->getVideoDriver();
	smanager = device->getSceneManager();
	gmanager = device->getGUIEnvironment();
	PushThis = gmanager->addButton(core::recti(10,10,150,50),0,0,L"Push me");
	device->getFileSystem()->addFileArchive("../data/export.tgz",1,1,io::EFAT_GZIP);
	device->getFileSystem()->addFileArchive("export.tar",1,1,io::EFAT_TAR);
	gmanager->getSkin()->setFont(gmanager->getFont("Invaders.xml"));
	//PushThis->set
}

void MenuIRRState::PrepareToStop()
{
	PushThis->setVisible(0);
}

void MenuIRRState::Start()
{
	PushThis->setVisible(1);
}

void MenuIRRState::Update()
{
	driver->beginScene(1, 1, video::SColor(255,199,10,15));
	this->ButtonControl();
    smanager->drawAll();
	gmanager->drawAll(),
	driver->endScene();
	//printf("button is %i\n", (int)PushThis->isPressed());
}

bool MenuIRRState::MayUpdate()
{
	return device->run();
}

bool MenuIRRState::ButtonControl()
{
	if(PushThis->isPressed())
	{
		GameState* _Game = GameState::Create(device);
		this->_Machine->PushState(_Game);
	}
	return 1;
}