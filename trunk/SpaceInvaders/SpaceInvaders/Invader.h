#ifndef _INVADER_H_
#define _INVADER_H_
#include "Basegameunit.h"
class Invader:public _bgunit
{
	public:
		enum InvaderType
		{
			model1 = 0,
			model2,
			model3,
			model4
		};
		Invader(scene::ISceneManager*, InvaderType);
		void MoveUP();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		void Fire();
		void Destroy();
		void SetPosition(core::vector3df&);
		float GetBoundX();
		float GetBoundY();
		const core::vector3df& GetPosition() const {return _node->getPosition();}
		void SetDestroyAnimator(scene::ISceneNodeAnimator*);
	private:
		static io::path models[];
		scene::ISceneNodeAnimator* destroyAnimator;
		
};
#endif