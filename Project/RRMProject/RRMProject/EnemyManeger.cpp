#include "EnemyManeger.h"
#include "EnemyFactory.h"

EnemyManeger::EnemyManeger() : _fac(new EnemyFactory())
{

}


EnemyManeger::~EnemyManeger()
{
	delete _fac;
}

void EnemyManeger::Update()
{
	_enemyList = _fac->GetEnemyList();
	for (Enemy* a : _enemyList)
	{
		a->Update();
	}
}

void EnemyManeger::Draw()
{
	for (Enemy* a : _enemyList)
	{
		a->Draw();
	}
}

void
EnemyManeger::Push(Enemy* enemy)
{
	_enemyList.push_back(enemy);
}

void
EnemyManeger::Delete()
{
	std::vector<Enemy*>::iterator itr;
	itr = _enemyList.begin();
	for (itr; itr != _enemyList.end(); ++itr)
	{
		itr = _enemyList.erase(itr);
	}
}
