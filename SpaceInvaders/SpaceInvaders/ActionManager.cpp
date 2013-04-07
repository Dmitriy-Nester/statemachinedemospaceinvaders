#include "STDAFX.H"
#include "ActionManager.h"
#include <irrlicht.h>
using namespace irr;
using namespace scene;
#include "Rocket.h"
#include "Invader.h"
#include "math.h"

ActionManager::ActionManager(float X, float Y, float Z, float Xc, float Yc, float Zc, ISceneManager* m)
{
	this->Single = NULL;
	LeftUP.Y = Y;
	LeftUP.X = X;
	LeftUP.Z = Z;
	this->RightDown.X = Xc;
	this->RightDown.Y = Yc;
	this->RightDown.Z = Zc;
	this->AddEnemiesInLevel(m);
	destroyAnimator1 = NULL;
	destroyAnimator2 = NULL;
	RocketExploseAnimator = NULL;
	//Enemy* nemy = new Enemy(m,Enemy::model2);
}

void ActionManager::Update(float FrameDelta)
{
//	printf("<%p>\n", this->Single);
	if(Single)
		Single->setFrameDelta(FrameDelta),
		Single->getVerticalPosition()<LeftUP.Y?this->Single->Rocket::MoveUP():this->AddObjectInDestroyStack(Single);
	this->UpdateEnemiesStates(FrameDelta);
	this->UpdateDestroyingObjects(FrameDelta);
}

void ActionManager::AddObjectInDestroyStack(_bgunit* object)
{
	object->Destroy();
	this->inDestroy.push_back(object);
	this->setRocket(NULL);
}

bool ActionManager::inScreen(float X, float Y, float Z)
{
	return (X>LeftUP.X&&X<RightDown.X)&&(Y<LeftUP.Y&&(Y>RightDown.Y));
}

void ActionManager::AddEnemiesInLevel(irr::scene::ISceneManager* m)
{
	RightLeft = 1;
	int l = 0;
	Enemy::InvaderType Type = Enemy::model1;
	int* pType = reinterpret_cast<int*>(&Type);
	core::vector3df buf(LeftUP.X+40, LeftUP.Y, LeftUP.Z);
	do
	{
		Enemy* nemy = new Enemy(m, Type);
		buf.X+=nemy->GetBoundX();
		if(l%8==0)
		{
			buf.Y-=nemy->GetBoundY();
			buf.X = LeftUP.X+40;
		}
		pType[0]+=((l+1)%8==0);
	//	printf("<%i>\n", (int)(l+1)%8);
		nemy->SetPosition(buf);
		this->enemies.push_back(nemy);
		l++;
	}
	while(l!=32);
}

void ActionManager::UpdateEnemiesStates(float FD)
{
	size_t u = this->enemies.size();
	Enemy* unit, *forDestroy = NULL;
	bool oneiterat = true;
	for(size_t f = 0; f!=u; f++)
	{
		unit = this->enemies[f];
		unit->setFrameDelta(FD);
		const core::vector3df& pos = unit->GetPosition();
		if(!this->inScreen(pos.X, pos.Y, pos.Z)&&oneiterat)
		{
						this->RightLeft=!this->RightLeft, 
						oneiterat = false;
						this->AllEnemiesStepDown();
		}
		if(ActionManager::InDangerZone(unit, Single))
		{
			this->AddObjectInDestroyStack(Single);
			this->AddObjectInDestroyStack(unit);
			forDestroy = unit;
		}
		this->RightLeft?unit->MoveLeft():unit->MoveRight();
	}
	if(forDestroy)
	{
		std::vector<Enemy*>::iterator iterat = this->enemies.begin();
		while(forDestroy!=*iterat)
						iterat++;
		this->enemies.erase(iterat);
	}
}

void ActionManager::AllEnemiesStepDown()
{	
	size_t count = this->enemies.size();
	for(size_t j = 0; j!=count;j++)
				enemies[j]->MoveDown();
}

bool ActionManager::InDangerZone(ActionManager::Enemy* _enemy, const Rocket* shoot)
{
	if(shoot)
	{
		float radius = (_enemy->GetBoundX()<_enemy->GetBoundY()?_enemy->GetBoundX():_enemy->GetBoundY())/2;
		return radius>shoot->GetPosition().getDistanceFrom(_enemy->GetPosition());
	}
	return 0;
}

void ActionManager::setDestroyAnimators(irr::scene::ISceneNodeAnimator *ja1, irr::scene::ISceneNodeAnimator * ja2)
{
	ja1->grab();
	ja2->grab();
	this->destroyAnimator1 = ja1;
	this->destroyAnimator2 = ja2;
	bool m;
	if(this->enemies.size())
	{
		size_t j = enemies.size();
		m = static_cast<bool>(j);//do you wanna random value, oh yes baby
		for(size_t k = 0; k!=j;k++)
		{
			m=!m;
			this->enemies[k]->SetDestroyAnimator(m?ja1:ja2);
		}
	}
}

void ActionManager::SetRocketExploseAnimator(irr::scene::ISceneNodeAnimator* REA)
{ 
	RocketExploseAnimator = REA;
	this->RocketExploseAnimator->grab();
}

void ActionManager::UpdateDestroyingObjects(float FRDT)
{
	unsigned int count = this->inDestroy.size();
	for(unsigned int j = 0; j!=count; j++)
	{
		this->inDestroy[j]->setFrameDelta(FRDT);
		this->inDestroy[j]->Destroy();
	}
}

const bool* ActionManager::HaveResult()
{
	if(!this->enemies.size()) //стек врагов пуст - победил
	{
		RezultGame = 1;
		return &RezultGame;
	}
	Enemy* last = this->enemies[this->enemies.size()-1];
	if(last->GetPosition().Y<this->RightDown.Y)//враги опустились низко - прогирал
	{
		RezultGame = 0;
		return &RezultGame;
	}
	return 0;
}

ActionManager::~ActionManager()
{
	unsigned int count = this->inDestroy.size();
	unsigned int j;
	for(j = 0; j!=count; j++)
				delete	this->inDestroy[j];
	count = this->enemies.size();
	for(j = 0; j!=count; j++)
		delete this->enemies[j];
}