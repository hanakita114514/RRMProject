#include "Spell.h"
#include "BulletManager.h"
#include "SinBullet.h"
#include "Bullet.h"

Spell::Spell()
{
	_freamCnt = 0;
	firstBullet = nullptr;
	bCnt = 0;
	_shotFlag = false;

}


Spell::~Spell()
{
}


void
Spell::AddList(Bullet* bullet)
{
	list.push_back(bullet);
}

void 
Spell::DeleteList()
{
	auto itr = list.begin();

	for (itr; itr != list.end();)
	{
		itr = list.erase(itr);
	}
}

void Spell::Shot()
{
	auto itr = list.begin();

	for (itr; itr != list.end(); ++itr)
	{
		(*itr)->Move();
	}
}

