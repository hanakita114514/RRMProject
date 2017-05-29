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

	//削除ループ
	//不要なもの削除ループ
	std::vector<Enemy*>::iterator it = _enemyList.begin();
	for (; it != _enemyList.end();)
	{
		if ((*it)->IsDead())
		{
			delete(*it);
			it = _enemyList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void EnemyManager::Draw(const Vector2& offset)
{
	for (auto& e : _enemyList)
	{
		e->Draw(offset);
	}
}

void
EnemyManager::Push(Enemy* enemy)
{
	_enemyList.push_back(enemy);
}

void 
EnemyManager::Create(const EnemyType& et)
{
	Enemy* newEnemy = _fac.Create(et);
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
		itr = _enemyList.erase(itr);
	}
}
