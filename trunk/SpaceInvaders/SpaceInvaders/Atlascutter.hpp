#ifndef _ATLASCUTTER_HPP_
#define _ATLASCUTTER_HPP_
#ifndef __IRRLICHT_H_INCLUDED__
#error irrlicht.h not include
#endif
struct AtlasCutter //“ак, данный текстурный атлас предстоить нарубать на анимации, дл€ этого нам нужна эта стрyктура
{
		AtlasCutter(scene::ISceneManager*);
		video::ITexture* getTextureAtIndex(u32);
		video::ITexture* getTextureAtlas();
		scene::ISceneNodeAnimator* getExploseAnimator1();
		scene::ISceneNodeAnimator* getExploseAnimator2();
		scene::ISceneNodeAnimator* getJetAnimator();
		scene::ISceneNodeAnimator* getRocketExploseAnimator();
		~AtlasCutter();
	private:
		scene::ISceneNodeAnimator* Explose1;
		scene::ISceneNodeAnimator* Explose2;
		scene::ISceneNodeAnimator* Jet, *RocketExplose;
		video::ITexture* _array[35];
		video::ITexture* Atlas;		
};
#endif