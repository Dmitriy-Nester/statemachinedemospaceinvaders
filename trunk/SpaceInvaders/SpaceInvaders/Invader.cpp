#include <STDAFX.H>
#include <irrlicht.h>
using namespace irr;
#include "invader.h"
io::path Invader::models[] =
{
	io::path("enemies_01.x"),
	io::path("enemies_02.x"),
	io::path("enemies_03.x"),
	io::path("enemies_04.x"),
};

Invader::Invader(irr::scene::ISceneManager *s, InvaderType type)
{
	manager = s;
	_node = manager->addAnimatedMeshSceneNode(s->getMesh(Invader::models[type]));
	core::aabbox3df box = _node->getBoundingBox();
	_node->setAnimationSpeed(240);
//	printf("<%f %f>\n", box.MaxEdge.X, box.MinEdge.X);
}

void Invader::SetPosition(core::vector3df& p)
{
	_node->setPosition(p);
}

float Invader::GetBoundX()
{
	core::aabbox3df box = _node->getBoundingBox();
	return box.MaxEdge.X*2;
}

float Invader::GetBoundY()
{
	core::aabbox3df box = _node->getBoundingBox();
	return box.MaxEdge.Y*2;
}

void Invader::MoveDown()
{
	core::vector3df pos = _node->getPosition();
	pos.Y -= 0.6;
	_node->setPosition(pos);
}

void Invader::MoveUP(){}

void Invader::SetDestroyAnimator(scene::ISceneNodeAnimator* d)
{
	this->destroyAnimator = d;
}

void Invader::MoveRight()
{
	core::vector3df pos = _node->getPosition();
	pos.X += 60*this->FrameDelta;
	_node->setPosition(pos);
}
void Invader::MoveLeft()
{
	core::vector3df pos = _node->getPosition();
	pos.X -= 60*this->FrameDelta;
	_node->setPosition(pos);
}
void Invader::Fire(){}
void Invader::Destroy()
{
	if(DeathTime==0.0f)
	{
		float X = this->GetBoundX();
		float Y = this->GetBoundY();
		X = X<Y?Y:X;
		core::vector3df ruidpos = _node->getPosition();
		_node->remove();
		DeathTime = 0.001f;
		_node = (scene::IAnimatedMeshSceneNode*)manager->addBillboardSceneNode(NULL,core::position2df(X,X),ruidpos);
		_node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		_node->addAnimator(this->destroyAnimator);
	}
	else
	{
		DeathTime+=FrameDelta;
		if(DeathTime>3.0f)
			_node->setVisible(0);
	}
}