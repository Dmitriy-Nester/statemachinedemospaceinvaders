#ifndef _MENUIRRSTATE_H_
#define _MENUIRRSTATE_H_
#ifndef _STATEMACHINE_HXX_
#error StateMachine class not found
#endif
#include <irrlicht.h>
using namespace irr;
class MenuIRRState:StateMachine::_state
{
	public:
		void Update();
		void PrepareToStop();
		void Start();
		bool MayUpdate();
		MenuIRRState();
	private:
		IrrlichtDevice *device;
		video::IVideoDriver* driver;
		scene::ISceneManager* smanager;
		gui::IGUIEnvironment* gmanager;
		gui::IGUIButton *PushThis;
		bool ButtonControl();
};
#endif
