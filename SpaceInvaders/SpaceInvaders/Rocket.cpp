#include "StdAFX.H"
#include <irrlicht.h>
using namespace irr;
#include "Rocket.h"

void Rocket::Launch(scene::ISceneManager *s, video::ITexture *JST, Rocket **pointer, _bgunit* Launcher)
{
	if(pointer)
	{
		*pointer = new Rocket(s,JST,Launcher);
		pointer[0]->external = pointer;
		/*pointer[0]->_node->grab();
		pointer[0]->_node->getParent()->removeChild(pointer[0]->_node);*/
	}
}

Rocket::Rocket(irr::scene::ISceneManager *s, irr::video::ITexture *JetStreamTexture, _bgunit* Launcher)
{
	manager = s;
	_node = manager->addAnimatedMeshSceneNode(manager->getMesh("rocket.x"));
	JetStream = manager->addBillboardSceneNode(_node, core::dimension2df(20,30));
	JetStream->setMaterialTexture(0, JetStreamTexture);
	JetStream->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	//_node->setMaterialFlag(video::EMF_LIGHTING, false);
	JetStream->setMaterialFlag(video::EMF_LIGHTING, false);
	JetStream->setPosition(core::vector3df(-1.0,-9,0));
	const core::vector3df& startpad = reinterpret_cast<Rocket*>(Launcher)->_node->getPosition();
	_node->setPosition(startpad);
}

void Rocket::MoveUP()
{
	core::vector3df buf = _node->getPosition();
	buf.Y += 270*this->FrameDelta;//180;
	//printf(">>X=%f Y=%f Z=%f<<\n", buf.X, buf.Y, buf.Z);
	_node->setPosition(buf);
}
void Rocket::Destroy()
{
	if(this->external)
	{
		this->external[0] = NULL;
		external = NULL;
		float X, Y;
		X = _node->getBoundingBox().MaxEdge.X;
		Y = _node->getBoundingBox().MaxEdge.Y;
		X = X<Y?Y:X;
		core::vector3df ruidpos = _node->getPosition();
		_node->removeAll();
		_node->remove();
		_node = NULL;
		JetStream = manager->addBillboardSceneNode(NULL, core::dimension2df(X,X), ruidpos);
		JetStream->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		JetStream->addAnimator(this->RocketExplose);
	}
	else
	{
		this->DeathTime += this->FrameDelta;
		if(this->DeathTime>3.0f)
			JetStream->setVisible(0);
	}
//	delete this;
}
