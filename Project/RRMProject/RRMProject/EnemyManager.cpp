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
	_enemyList = _fac->GetEnemyList();
	for (Enemy* a : _enemyList)
	{
		a->Update();
	}
}

void EnemyManager::Draw()
{
	for (Enemy* a : _enemyList)
	{
		a->Draw();
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
