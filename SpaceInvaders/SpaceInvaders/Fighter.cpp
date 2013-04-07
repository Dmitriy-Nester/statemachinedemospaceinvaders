#include "STDAFX.H"
#include <irrlicht.h>
using namespace irr;
#include "Fighter.h"
#include "Rocket.h"

Fighter::Fighter(irr::scene::ISceneManager *m)
{
	this->manager = m;
	_node = manager->addAnimatedMeshSceneNode(manager->getMesh("fighter.x"));
	_node->setMaterialFlag(video::EMF_LIGHTING, false);
	_node->setRotation(core::vector3df(-30,0,0));
	_node->setAnimationSpeed(30);
	this->LeftDuza = manager->addBillboardSceneNode(0, core::dimension2df(10,30));
	this->RightDuza = manager->addBillboardSceneNode(0, core::dimension2df(10,30));
	_node->addChild(RightDuza);
	_node->addChild(LeftDuza);
//	LeftDuza->setMaterialFlag(video::EMF_LIGHTING, false);
//	RightDuza->setMaterialFlag(video::EMF_LIGHTING, false);
	LeftDuza->setPosition(core::vector3df(-3,-16,-18));
	RightDuza->setPosition(core::vector3df(5,-16,-18));
	LeftDuza->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	RightDuza->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	Weapon = NULL;
}

void Fighter::Fire()
{
//	printf("Fire!!!\n");
	if(!Weapon)
	{
		Rocket::Launch(manager, JetRocketTexure, &Weapon, this);
		Weapon->SetRocketExploseAnimation(Amanager->GetRocketExploseAnimator());
		Amanager->setRocket(Weapon);
	}
}

void Fighter::MoveUP(){}//нет движения по этим координатам
void Fighter::MoveDown(){}

void Fighter::MoveRight()
{
	core::vector3df pos =  _node->getPosition();
	pos.X+=700*FrameDelta*Amanager->inScreen(pos.X+10, pos.Y, pos.Z);
	_node->setPosition(pos);
}

void Fighter::MoveLeft()
{
	core::vector3df pos = _node->getPosition();
	pos.X-=700*FrameDelta*Amanager->inScreen(pos.X-10, pos.Y, pos.Z);
	_node->setPosition(pos);
}

void Fighter::setJetTexture(irr::video::ITexture *texture)
{
	LeftDuza->setMaterialTexture(0,texture);
	RightDuza->setMaterialTexture(0, texture);
}

void Fighter::Destroy()
{
	;
}

Fighter::~Fighter()
{
	
}