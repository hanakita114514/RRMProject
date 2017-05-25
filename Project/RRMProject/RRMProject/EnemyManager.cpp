#include "EnemyManager.h"
#include "EnemyFactory.h"

EnemyManager::EnemyManager() : _fac(new EnemyFactory())
{

}


EnemyManager::~EnemyManager()
{
	delete _fac;
}

void EnemyManager::Update()
{
	std::vector<Enemy*>& enemyList = _fac->GetEnemyList();
	for (auto e : enemyList)
	{
		e->Update();
	}

	//削除ループ
	//不要なもの削除ループ
	std::vector<Enemy*>::iterator it = enemyList.begin();
	for (; it != enemyList.end();)
	{
		if ((*it)->IsDead())
		{
			delete(*it);
			it = enemyList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void EnemyManager::Draw()
{
	std::vector<Enemy*>& enemyList = _fac->GetEnemyList();
	for (auto e : enemyList)
	{
		e->Draw();
	}
}

void
EnemyManager::Push(Enemy* enemy)
{
	_enemyList.push_back(enemy);
}

void
EnemyManager::Delete()
{
	std::vector<Enemy*>::iterator itr;
	itr = _enemyList.begin();
	for (itr; itr != _enemyList.end(); ++itr)
	{
		itr = _enemyList.erase(itr);
	}
}
