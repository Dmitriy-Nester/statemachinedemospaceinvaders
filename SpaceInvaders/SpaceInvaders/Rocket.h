#ifndef _ROCKET_H_
#define _ROCKET_H_
#include "BaseGameUnit.h"
class Rocket:public _bgunit
{
	private:
		Rocket(scene::ISceneManager*, video::ITexture*, _bgunit*);
		Rocket** external;
		scene::IBillboardSceneNode* JetStream;
		scene::ISceneNodeAnimator* RocketExplose;
	public:
		static void Launch(scene::ISceneManager*, video::ITexture*, Rocket**, _bgunit*);
		void MoveUP();
		void MoveDown(){}
		void MoveRight(){}
		void MoveLeft(){}
		void Fire(){};
		void Destroy();
		float getVerticalPosition(){return _node->getPosition().Y;}
		const core::vector3df& GetPosition() const {return _node->getPosition();}
		void SetRocketExploseAnimation(scene::ISceneNodeAnimator* RE){this->RocketExplose = RE;}
};
#endif