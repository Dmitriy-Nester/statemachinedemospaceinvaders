#ifndef _STATEMACHINE_HXX_
#define _STATEMACHINE_HXX_
#include <vector>
class StateMachine
{
	public:
	struct _state //Base for game states 
	{
		protected:
			StateMachine* _Machine;
		public:
			_state(){_Machine = NULL;}
		virtual void Update() = 0;
		virtual void PrepareToStop() = 0;
		virtual void Start() = 0;
		virtual ~_state(){};
		virtual bool MayUpdate() = 0;
		void SetMachine(StateMachine* _){_Machine=_;}		
	};
	StateMachine(_state*);// start Machine whith start state
	private:
		std::vector<_state*> StatesStack;
		_state *CurrentState;
	public:
		void Update();
		_state* PopState();
		void PushState(_state*);
		void SetState(_state*);
}; 
#endif