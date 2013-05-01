#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_
#include "StateMachine.hxx"
#ifndef __IRRLICHT_H_INCLUDED__
#error irrlicht.h not include
#endif
namespace irr
{
	class IrrlichtDevice;
	namespace video
	{
		class IVideoDriver;
	}
}
class PauseState:StateMachine::_state
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
};
#endif