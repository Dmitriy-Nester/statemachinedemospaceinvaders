#ifndef _FIGHTER_H_
#define _FIGHTER_H_
#include "BaseGameUnit.h"
#include "ActionManager.h"
class Rocket;
class Fighter: public _bgunit
{
	private:
		scene::IBillboardSceneNode* LeftDuza, *RightDuza;
		Rocket* Weapon;
		video::ITexture* JetRocketTexure;
		ActionManager* Amanager;
	public:
		Fighter(scene::ISceneManager*);
		void MoveUP();
		void MoveDown();
		void Fire();
		void Destroy();
		void MoveLeft();
		void MoveRight();
		~Fighter();
		void setJetTexture(video::ITexture*);
		void setJetRocketTexture(video::ITexture* x){JetRocketTexure = x;}
		void setActionManager(ActionManager* A){Amanager = A;}
};
#endif