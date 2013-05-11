#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_
#include "StateMachine.hxx"
#ifndef __IRRLICHT_H_INCLUDED__
#error irrlicht.h not include
#endif

class PauseState:public StateMachine::_state
{
	public:
		void Update();
		void PrepareToStop();
		void Start();
		bool MayUpdate();
		PauseState(irr::IrrlichtDevice*);
	private:
		irr::IrrlichtDevice& device;
		irr::video::IVideoDriver* driver;
		irr::scene::ISceneManager* manager;
		irr::gui::IGUIEnvironment* guienv;
		irr::gui::IGUIStaticText* PauseMessage;
		struct PauseReceiver:public irr::IEventReceiver
		{
			StateMachine* machine;
			bool OnEvent(const irr::SEvent&);
			PauseReceiver(){machine = NULL;}
			bool keyUP;			
		};
		PauseReceiver Receiver;
};
#endif