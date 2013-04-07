#ifndef _BGUNIT_H_
#define _BGUNIT_H_
#ifndef __IRRLICHT_H_INCLUDED__
#error irrlicht.h not include
#endif
class _bgunit //Base Game Unit
{
	protected:
	  scene::IAnimatedMeshSceneNode* _node;
	  scene::ISceneManager* manager;
	  double FrameDelta, DeathTime;
	  _bgunit(){DeathTime = NULL;}
	public:
	  void virtual MoveLeft() = 0;
	  void virtual MoveRight() = 0;
	  void virtual MoveUP() = 0;
	  void virtual MoveDown() = 0;
	  void virtual Fire() = 0;
	  void virtual Destroy() = 0;
	  void setFrameDelta(double f){FrameDelta = f;}
	  bool inDestroy(){return DeathTime==0.0f;}
	  virtual ~_bgunit(){if(_node)_node->removeAll();}
};
#endif