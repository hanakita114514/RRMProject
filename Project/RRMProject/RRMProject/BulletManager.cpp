#include  <DxLib.h>
#include "BulletManager.h"
#include "GameMain.h"

BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

void BulletManager::Update()
{
		//====================================================================
		for (auto b : _bulletList)
		{
			if (b->IsAlive())
			{
				b->Update();
			}
		}
		//=====================================================================
}

void BulletManager::Draw()
{
	for (auto b : _bulletList)
	{
		if (b->IsAlive())
		{
			b->Draw();
		}
	}
}

Bullet* 
BulletManager::Create(const BulletType& bulletID, Vector2 vec, ObjectType type, Vector2 entry, Object* owner)
{
	//g‚¦‚é’e‚ÌŒŸõ
	for (auto b : _bulletList)
	{
		if (b->GetID() == bulletID && !b->IsAlive())
		{
			b->Initialize(vec, type);
			return b;
		}
	}

	//g‚¦‚é’e‚ª‚È‚¢ê‡V‚½‚É¶¬
	Bullet* newBullet = _fac.Create(bulletID, vec, type, entry);
	_bulletList.push_back(newBullet);

	return newBullet;
}


void
BulletManager::Delete()
{
	std::vector<Bullet*>::iterator itr;
	itr = _bulletList.begin();

	for (itr; itr != _bulletList.end(); itr++)
	{
		itr = _bulletList.erase(itr);
	}
}

void 
BulletManager::Delete(Object* owner)
{
	std::vector<Bullet*>::iterator itr;
	itr = _bulletList.begin();

	for (itr; itr != _bulletList.end(); itr++)
	{
		itr = _bulletList.erase(itr);
	}
}

std::vector<Bullet*> 
BulletManager::GetBulletList()
{
	return _bulletList;
}