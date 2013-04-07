#ifndef _RESULTSTATE_H_
#define _RESULTSTATE_H_
#ifndef __IRRLICHT_H_INCLUDED__
#error irrlicht.h not include
#endif
#include "StateMachine.hxx"
class ResultState:public StateMachine::_state
{
	public:	
		bool MayUpdate();
		void PrepareToStop();
		void Start();
		void Update();
		ResultState(irr::IrrlichtDevice*, bool);
		~ResultState();
	private:
		bool GameResult;
		irr::IrrlichtDevice* device;
		gui::IGUIEnvironment* Envir;
		scene::ISceneManager* Smanager;
		gui::IGUIStaticText* message;
		video::IVideoDriver* driver;
		gui::IGUIButton* BackToMenu;
		void BackToStart();
};
#endif