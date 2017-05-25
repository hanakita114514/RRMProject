#pragma once
#include "Enemy.h"
#include <vector>

class EnemyFactory;

class EnemyManager
{
private:
	std::vector<Enemy*> _enemyList;
	EnemyFactory* _fac;
	EnemyManager();
	EnemyManager(const EnemyManager&);
	EnemyManager& operator = (const EnemyManager&);

public:
	~EnemyManager();

	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}

	void Update();						//XV
	void Draw();						//•`‰æ
	void Push(Enemy* enemy);
	void Delete();

	EnemyFactory* GetEnemyFac() { return _fac; }
};

