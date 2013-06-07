#include "STDAFX.H"
#include <irrlicht.h>
using namespace irr;
#include "Atlascutter.hpp"

#ifndef _MSC_VER
#define sprintf_s(A,B,C,D) sprintf(A,C,D)
#endif

AtlasCutter::AtlasCutter(irr::scene::ISceneManager *smangr):Atlas(smangr->getVideoDriver()->getTexture("particle_atlas_additive.tga"))
{
	video::IVideoDriver *driver = smangr->getVideoDriver();
	video::IImage* buf = NULL;
	char name[30];
	char format[] = "Atlas cut %i";
	char stripes[] = "stripes";
	char j1[] = "jet1";
	char j2[] = "jet2";
	int num = 0;
	if(!driver->findTexture(stripes))//есть такие имена текстур ?
	{
		for(int v = 0;v!=256;v+=64)//нет, надо порезать
		{
			for(int s = 0;s!=512;s+=64)
			{
				buf = driver->createImage(Atlas,core::vector2di(s,v),core::dimension2du(64,64));
				sprintf_s(name, 30, format, num);
				_array[num] = driver->addTexture(name,buf);
				num++;
				buf->drop();				
			}
		}
		//--алгоритмы кончились, резать атлас харткодно
		buf = driver->createImage(Atlas, core::vector2di(0,448),core::dimension2du(64,64));
		_array[32] = driver->addTexture(stripes,buf);
		buf->drop();
		buf = driver->createImage(Atlas, core::vector2di(320,320),core::dimension2du(64,192));
		_array[33] = driver->addTexture(j1,buf);
		buf->drop();
		buf = driver->createImage(Atlas, core::vector2di(384,320),core::dimension2du(128,192));
		_array[34] = driver->addTexture(j2,buf);
		buf->drop();
		//--все, атлас нарезан, теперь генерим аниматоры
	}
	else //просто из памяти драйвера достать
	{
		for(num = 0;num!=32;num++)
		{
			sprintf_s(name, 30, format, num);
			_array[num] = driver->findTexture(name);
		}
		_array[32] = driver->findTexture(stripes);
		_array[33] = driver->findTexture(j1);
		_array[34] = driver->findTexture(j2);
	}
	core::array<video::ITexture*> arbuf;
	for(num = 0; num!=16;num++)
			arbuf.insert(_array[num],num);//что-то пушбек работает с крешами, надо заменить
	this->Explose1 = smangr->createTextureAnimator(arbuf,1,true);//,1,0);
	arbuf.clear();
	while(num!=32)
	{
		arbuf.insert(_array[num],num-16);
		num++;
	} 
	this->Explose2 = smangr->createTextureAnimator(arbuf, 1,true);
	arbuf.clear();
	arbuf.push_front(_array[33]);
	arbuf.push_front(_array[34]);
	Jet = smangr->createTextureAnimator(arbuf, 1,true);
	arbuf.clear();
	//--нужно создать аниматор для ракеты для взрыва ракеты, он будет уникален или напохож на другие
	int a = -2, b = 15;
	for(num = 1; num!=17; num++)
				arbuf.push_front(_array[num%2?(b+=2):(a+=2)]);
	arbuf.insert(_array[32],0);
	//---
	RocketExplose = smangr->createTextureAnimator(arbuf,1); 
}

video::ITexture* AtlasCutter::getTextureAtIndex(irr::u32 u)
{
	return _array[u];
}

video::ITexture* AtlasCutter::getTextureAtlas()
{
	return Atlas;
}

scene::ISceneNodeAnimator* AtlasCutter::getExploseAnimator1()
{
	return Explose1;
}

scene::ISceneNodeAnimator* AtlasCutter::getExploseAnimator2()
{
	return Explose2;
}

scene::ISceneNodeAnimator* AtlasCutter::getJetAnimator()
{
	return Jet;
}

scene::ISceneNodeAnimator* AtlasCutter::getRocketExploseAnimator()
{
	return RocketExplose;
}

AtlasCutter::~AtlasCutter()
{
	Jet->drop();
	Explose1->drop();
	Explose2->drop();
	RocketExplose->drop();
	/*for(int i = 0;i!=35;i++)
				_array[i]->drop();*/
}