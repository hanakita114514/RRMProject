#include  <RRMLib.h>
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

void BulletManager::Draw(const Vector2& offset)
{
	for (auto b : _bulletList)
	{
		if (b->IsAlive())
		{
			b->Draw(offset);
		}
	}
}

Bullet* 
BulletManager::Create(const BulletType& bulletID, const Position& pos, Vector2 vec, ObjectType type, Vector2 entry, Object* owner)
{
	//使える弾の検索
	for (auto b : _bulletList)
	{
		if (b->GetID() == bulletID && !b->IsAlive())
		{
			b->SetOwner(owner);
			b->Initialize(pos, vec, type);
			return b;
		}
	}

	//使える弾がない場合新たに生成
	Bullet* newBullet = _fac.Create(bulletID, pos ,vec, type, entry);
	newBullet->SetOwner(owner);
	_bulletList.push_back(newBullet);

	return newBullet;
}


void
BulletManager::Delete()
{
	std::vector<Bullet*>::iterator itr;
	itr = _bulletList.begin();

	for (itr; itr != _bulletList.end();)
	{
		delete (*itr);
		itr = _bulletList.erase(itr);
	}
}

void 
BulletManager::Delete(Object* owner)
{
	std::vector<Bullet*>::iterator itr;
	itr = _bulletList.begin();

	for (; itr != _bulletList.end();)
	{
		if ((*itr)->GetOwner() == owner)
		{
			delete(*itr);
			itr = _bulletList.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

std::vector<Bullet*>&
BulletManager::GetBulletList()
{
	return _bulletList;
}