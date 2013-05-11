#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#ifndef _STATEMACHINE_HXX_
#error StateMachine class not found
#endif
#ifndef __IRRLICHT_H_INCLUDED__
#error irrlicht.h not include
#endif
class _bgunit;
class ActionManager;
class GameState:public StateMachine::_state
{
	public:
		static GameState* Create(IrrlichtDevice* i){return new GameState(i);}
		void Update();
		void PrepareToStop();
		void Start();
		bool MayUpdate();
		~GameState();
		class GameEventReceiver:public IEventReceiver
		{
			public:
				void setBackToMenuEvent(void (*)(GameState*), GameState*);
			private:
				bool OnEvent(const SEvent&);
				void (*BackToMenu)(GameState*);
				GameState* BTM;				 
		};
		void SwitchToRezultScreen(bool);
	private:
		GameState(IrrlichtDevice*);
		IrrlichtDevice *device;
		scene::ISceneManager* smanager;
		video::IVideoDriver* driver;
		scene::ISceneNode* SkyBox;
		scene::ICameraSceneNode* Camera;
		GameEventReceiver Receiver;	
		static void DestroyThisAndPopPrevious(GameState*);
		_bgunit* GamerUnit;		
		unsigned int now, then;
		ActionManager* Manager;
		_state* pauseState;
};
#endif