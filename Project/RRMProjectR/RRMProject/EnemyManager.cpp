#include "EnemyManager.h"
#include "EnemyFactory.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
	Delete();
}

void EnemyManager::Update()
{
	for (auto& e : _enemyList)
	{
		e->Update();
	}

	for (auto& r : _reservation)
	{
		_enemyList.push_back(r);
	}
	_reservation.clear();

}

int 
EnemyManager::DeleteUpdate()
{
	//削除ループ
	//不要なもの削除ループ
	int deleteNum = 0;

	std::vector<Enemy*>::iterator it = _enemyList.begin();
	for (; it != _enemyList.end();)
	{
		if ((*it)->IsDead())
		{
			delete(*it);
			*it = nullptr;
			it = _enemyList.erase(it);
			++deleteNum;
		}
		else
		{
			it++;
		}
	}

	return deleteNum;
}

void EnemyManager::Draw(const Vector2& offset)
{
	for (auto& e : _enemyList)
	{
		e->Draw(offset);
	}
}

void 
EnemyManager::ScreenLimit(Camera& camera)
{
	for (auto& e : _enemyList)
	{
		e->ScreenLimit(camera);
	}
}

void 
EnemyManager::Create(const EnemyType& et, const Position& pos)
{
	Enemy* newEnemy = _fac.Create(et, pos);
	_enemyList.push_back(newEnemy);
}

void
EnemyManager::Create(const EnemyType& et, const Position& pos, const Position& playerPos, Camera& camera)
{
	Enemy* newEnemy = _fac.Create(et, pos, playerPos, camera);
	_enemyList.push_back(newEnemy);
}

void
EnemyManager::Delete()
{
	std::vector<Enemy*>::iterator itr;
	itr = _enemyList.begin();
	for (itr; itr != _enemyList.end();)
	{
		delete (*itr);
		*itr = nullptr;
		itr = _enemyList.erase(itr);
	}
}

bool
EnemyManager::EnemyEradication()
{
	if (_enemyList.size() == 0)
	{
		return true;
	}

	return false;
}

void 
EnemyManager::AddList(const EnemyType& et, const Position& pos)
{
	_reservation.push_back(_fac.Create(et,pos));
}