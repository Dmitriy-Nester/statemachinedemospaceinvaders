#ifndef _ACTIONMANAGER_H_
#define _ACTIONMANAGER_H_
#include <vector>
class Rocket;
class Invader;
class _bgunit;
namespace irr
{
	namespace scene
	{
		class ISceneManager;
		class ISceneNodeAnimator;
	}	
}

class ActionManager
{
	private:
		typedef Invader Enemy;
		Rocket* Single;
		std::vector<Enemy*> enemies;
		std::vector<_bgunit*> inDestroy;
		irr::scene::ISceneNodeAnimator* destroyAnimator1, *destroyAnimator2, *RocketExploseAnimator;
		struct Corner
		{
			float X, Y, Z; 
		};
		Corner LeftUP, RightDown;
		void AddObjectInDestroyStack(_bgunit*);
		void AddEnemiesInLevel(irr::scene::ISceneManager*);
		void UpdateEnemiesStates(float);//float is frame delta
		bool RightLeft, RezultGame;//true==right & false == left;//true==win &false loze;
		void AllEnemiesStepDown();
		void UpdateDestroyingObjects(float);
	public:
		void setDestroyAnimators(irr::scene::ISceneNodeAnimator*, irr::scene::ISceneNodeAnimator*);
		void Update(float);//float is frame delta
		ActionManager(float X, float Y, float Z, float Xc, float Yc, float Zc, irr::scene::ISceneManager*);//corners screen coordinat for concrete resolution
		inline  void setRocket(Rocket* R){Single = R;}
		bool inScreen(float X, float Y, float Z);
		void SetRocketExploseAnimator(irr::scene::ISceneNodeAnimator*);
		irr::scene::ISceneNodeAnimator* GetRocketExploseAnimator(){return RocketExploseAnimator;}
		static bool InDangerZone(Enemy*, const Rocket*);
		const bool* HaveResult();
		~ActionManager();
};
#endif